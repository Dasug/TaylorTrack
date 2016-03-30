/*
The MIT License (MIT)

Copyright (c) 2015 Marius Kaufmann, Tamara Frieß, Jannis Hoppe, Christian Hack

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/**
 * @file
 * @brief Contains the implementation for the class taylortrack::input::MicrophoneInputStrategy
 * as well as a callback function used within the class.
 */
#include "input/microphone_input_strategy.h"
#include <strings.h>

namespace taylortrack {
namespace input {

namespace {
/**
 * @brief Callback function called when receiving audio data.
 * @sa For a more detailed Documentation of this method please refer to http://portaudio.com/docs/v19-doxydocs/
 */
int PaStreamCallback(const void *input,
                     void *output,
                     unsigned long frameSamples,
                     const PaStreamCallbackTimeInfo *timeInfo,
                     PaStreamCallbackFlags statusFlags,
                     void *userData) {
  // casting void pointers to needed data types
  const float **float_input =
      reinterpret_cast<const float**>(const_cast<void*>(input));
  MicrophoneStreamData *stream_data =
      reinterpret_cast<MicrophoneStreamData*>(userData);

  // Do we need new data? If not, just skip it.
  if (!stream_data->has_written) {
    int number_of_channels = stream_data->channel_number;

    // Clear existing data
    for (int channel = 0; channel < number_of_channels; ++channel) {
      stream_data->values[channel].clear();
    }

    // Fill in sample values (read one sample from each channel at a time)
    for (int frame = 0; frame < static_cast<int>(frameSamples); ++frame) {
      for (int channel = 0; channel < number_of_channels; ++channel) {
        stream_data->values[channel].push_back(*float_input[channel]++);
      }
    }

    // Mark data as available
    stream_data->has_written = true;
  }

  // make sure the compiler shuts up about unused variables
  static_cast<void>(output);
  static_cast<void>(timeInfo);
  static_cast<void>(statusFlags);
  return 0;
}
}  // namespace

yarp::os::Bottle MicrophoneInputStrategy::read(yarp::os::Bottle *bottle) {
  // Are we recording? If not, start recording
  if (!running_) {
    running_ = true;

    // Initialize PortAudio Stream for each microphone in the config file
    for (auto microphone_device : microphone_devices_) {
      PaStream *stream;  // create PortAudio Stream, will be filled by PortAudio

      // Initialize Stream Data
      MicrophoneStreamData *stream_data = new MicrophoneStreamData;
      stream_data->channel_number = microphone_device.channels;
      stream_data->values.resize(
          static_cast<uint64_t>(microphone_device.channels));

      // Initialize Stream Parameters
      PaStreamParameters input_parameters;

      // Fill Input Parameters with Zeros, so that it doesn't use random values
      bzero(&input_parameters, sizeof(input_parameters));

      // Fill in input parameters
      const PaDeviceInfo *deviceInfo =
          Pa_GetDeviceInfo(microphone_device.microphone_id);
      input_parameters.device = microphone_device.microphone_id;
      input_parameters.channelCount = microphone_device.channels;
      input_parameters.sampleFormat = paFloat32 | paNonInterleaved;
      input_parameters.suggestedLatency =
          deviceInfo->defaultLowInputLatency;
      input_parameters.hostApiSpecificStreamInfo = NULL;

      // Don't use any special stream flags
      PaStreamFlags flags = paNoFlag;

      // Open Stream and check for error
      error_ = Pa_OpenStream(&stream,
                             &input_parameters,
                             nullptr,  // We don't need any output, so we pass a null pointer
                             settings_.sample_rate,
                             static_cast<uint64_t>(settings_.frame_size),
                             flags,
                             PaStreamCallback,
                             stream_data);

      if (error_ != paNoError) {
        std::cout << Pa_GetErrorText(error_) << std::endl;
      }

      // Save streams and stream data objects
      streams_.push_back(stream);
      stream_datas_.push_back(stream_data);
    }

    // Try starting all streams roughly at the same time
    for (auto stream : streams_) {
      Pa_StartStream(stream);
    }
  }

  // Check if all devices are ready for reading the data
  bool all_devices_available = true;
  for (auto stream_data : stream_datas_) {
    if (!stream_data->has_written) {
      all_devices_available = false;
      break;
    }
  }

  if (all_devices_available) {
    // Add one sample from every channel at a time to the bottle
    for (int sample_id = 0; sample_id < settings_.frame_size; ++sample_id) {
      for (auto &stream_data : stream_datas_) {
        for (int current_channel_id = 0;
             current_channel_id < stream_data->channel_number;
             ++current_channel_id) {
          bottle->addDouble(stream_data->values[current_channel_id][sample_id]);
        }
      }
    }

    // Mark all streams as ready to receive data again
    for (auto &stream_data : stream_datas_) {
      stream_data->has_written = false;
    }
  }
  return *bottle;
}

bool MicrophoneInputStrategy::is_done() {
  return (error_ != paNoError) || done_;
}

void MicrophoneInputStrategy::set_parameters(const utils::Parameters &params) {
  // just ignore all parameters for now
}

void MicrophoneInputStrategy::set_config(
    const utils::ConfigParser &config_parser) {
  // Close all existing streams
  for (auto stream : streams_) {
    Pa_CloseStream(stream);
  }

  // Set Data fields
  settings_ = config_parser.get_microphone_input_configuration();
  microphone_devices_ = settings_.devices;
  channels_ = 0;

  // Acquire and display information about selected devices
  if (microphone_devices_.size() > 0) {
    PaDeviceIndex devices = Pa_GetDeviceCount();
    for (auto &device : microphone_devices_) {
      if (device.microphone_id <= devices) {
        const PaDeviceInfo *current_device =
            Pa_GetDeviceInfo(device.microphone_id);
        std::cout << "Found device " << device.microphone_id << ": "
                  << current_device->name << std::endl;
        std::cout << "    " << current_device->maxInputChannels << " channels, "
                  << "delay: " << device.delay << " samples" << std::endl;
        channels_ += current_device->maxInputChannels;
        device.channels = current_device->maxInputChannels;
      } else {
        std::cout << "Error: Microphone device " << device.microphone_id
                  << " could not be located!" << std::endl;
        done_ = true;
      }
    }

    if (!done_) {
      std::cout << "Channels in total: " << channels_ << std::endl;
    }
  } else {
    std::cout << "Error: No microphones defined!" << std::endl;
    done_ = true;
  }
}

MicrophoneInputStrategy::MicrophoneInputStrategy() {
  std::cout << "Initializing PortAudio..." << std::endl;
  error_ = Pa_Initialize();
  if (error_ != paNoError) {
    done_ = true;
    std::cout << "PortAudio error_: " << Pa_GetErrorText(error_) << std::endl;
  } else {
    // Display information about all available devices
    PaDeviceIndex devices = Pa_GetDeviceCount();
    std::cout << "Found " << devices << " audio devices:" << std::endl;
    for (PaDeviceIndex device = 0; device < devices; ++device) {
      std::cout << device << ": "
                << Pa_GetDeviceInfo(device)->name << std::endl;
    }
  }
}

MicrophoneInputStrategy::~MicrophoneInputStrategy() {
  // Terminate Port Audio
  if (error_ == paNoError) {
    PaError error = Pa_Terminate();
    if (error != paNoError) {
      std::cout << "PortAudio error: " << Pa_GetErrorText(error) << std::endl;
    }
  }

  // Delete Stream Datas
  for (auto stream_data : stream_datas_) {
    delete stream_data;
  }
}

}  // namespace input
}  // namespace taylortrack
