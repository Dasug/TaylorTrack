#include <zconf.h>
//#include <tkPort.h>
#include "microphone_input_strategy.h"

namespace taylortrack {
namespace input {

namespace {
int PaStreamCallback(const void *input, void *output, unsigned long frameCount,
                     const PaStreamCallbackTimeInfo* timeInfo,
                     PaStreamCallbackFlags statusFlags, void *userData) {
  const float** float_input = reinterpret_cast<const float**>(const_cast<void*>(input));
  MicrophoneStreamData* stream_data = reinterpret_cast<MicrophoneStreamData*>(userData);

  // Do we need new data? If not, just skip it.
  if (!stream_data->has_written) {
    //std::cout << "Writing into Stream Data #" << stream_data->device.microphone_id << std::endl;
    // Create one vector for each channel
    std::vector<std::vector<double>> values;
    for (int channel = 0; channel < stream_data->channel_number; ++channel) {
      std::vector<double> channel_values;
      values.push_back(channel_values);
    }
    int channelNumber = stream_data->channel_number;

    for (int channel = 0; channel < channelNumber; ++channel) {
      stream_data->values[channel].clear();
    }
    // Fill in sample values

    for (int frame = 0; frame < static_cast<int>(frameCount); ++frame) {
      for (int channel = 0; channel < channelNumber; ++channel) {
        stream_data->values[channel].push_back(*float_input[channel]++);
      }
    }

    //stream_data->values.resize(static_cast<unsigned long>(stream_data->channel_number));

    stream_data->has_written = true;
  }

  // make sure the compiler shuts up about unused variables
  static_cast<void>(output);
  static_cast<void>(timeInfo);
  static_cast<void>(statusFlags);
  return 0;
}
}

yarp::os::Bottle MicrophoneInputStrategy::read(yarp::os::Bottle &bottle) {
  if(!running_) {
    running_ = true;
    for (auto microphone_device : microphone_devices_) {
      PaStream *stream;
      MicrophoneStreamData* stream_data = new MicrophoneStreamData;
      //stream_data.input_strategy = this;
      stream_data->device = microphone_device;
      stream_data->channel_number = microphone_device.channels;
      stream_data->values.resize(static_cast<unsigned long>(microphone_device.channels));
      PaStreamParameters input_parameters;
      PaStreamParameters output_parameters;
      bzero(&input_parameters, sizeof(input_parameters));
      input_parameters.device = microphone_device.microphone_id;
      input_parameters.channelCount = microphone_device.channels;
      input_parameters.sampleFormat = paFloat32 | paNonInterleaved;
      input_parameters.suggestedLatency = Pa_GetDeviceInfo(microphone_device.microphone_id)->defaultLowInputLatency;
      input_parameters.hostApiSpecificStreamInfo = NULL;

      bzero(&output_parameters, sizeof(output_parameters));

      PaStreamFlags flags = paNoFlag;

      error_ = Pa_OpenStream(&stream, &input_parameters, nullptr, settings_.sample_rate,
                    static_cast<unsigned long>(settings_.frame_size), flags, PaStreamCallback, stream_data);
      if(error_ != paNoError) {
        std::cout << Pa_GetErrorText(error_) << std::endl;
      }
      streams_.push_back(stream);
      stream_datas_.push_back(stream_data);
    }
    for (auto stream : streams_) {
      Pa_StartStream(stream);
    }
  }

  Pa_Sleep(200);
  bool all_devices_available = true;
  for (auto stream_data : stream_datas_) {
    if(!stream_data->has_written) {
      all_devices_available = false;
      break;
    }
  }

  if (all_devices_available) {
    for (int sample_id = 0; sample_id < settings_.frame_size; ++sample_id) {
      for (auto &stream_data : stream_datas_) {
        for (int current_channel_id = 0; current_channel_id < stream_data->channel_number; ++current_channel_id) {
          //std::cout << stream_data->values[current_channel_id][sample_id] << std::endl;
          bottle.addDouble(stream_data->values[current_channel_id][sample_id]);
        }
      }
    }

    for (auto &stream_data : stream_datas_) {
      stream_data->has_written = false;
    }
  }
  return bottle;
}

bool MicrophoneInputStrategy::is_done() {
  return (error_ != paNoError) || done_;
}

void MicrophoneInputStrategy::set_parameters(const utils::Parameters &params) {
  // just ignore all parameters for now
}

void MicrophoneInputStrategy::set_config(const utils::ConfigParser &config_parser) {
  settings_ = config_parser.get_microphone_input_configuration();
  microphone_devices_ = settings_.devices;
  channels_ = 0;
  if(microphone_devices_.size() > 0) {
    PaDeviceIndex devices = Pa_GetDeviceCount();
    for (auto &device : microphone_devices_) {
      if(device.microphone_id <= devices) {
        const PaDeviceInfo* current_device = Pa_GetDeviceInfo(device.microphone_id);
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

    channel_values_.resize(static_cast<unsigned long>(channels_));
    device_data_available_.clear();
    for (int device = 0; device < static_cast<int>(microphone_devices_.size()); ++device) {
      device_data_available_.push_back(false);
    }

    if(!done_) {
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
    PaDeviceIndex devices = Pa_GetDeviceCount();
    std::cout << "Found " << devices << " audio devices:" << std::endl;
    for (PaDeviceIndex device = 0; device < devices; ++device) {
      std::cout << device << ": " << Pa_GetDeviceInfo(device)->name << std::endl;
    }
  }
}

MicrophoneInputStrategy::~MicrophoneInputStrategy() {
  if (error_ == paNoError) {
    PaError error = Pa_Terminate();
    if( error != paNoError ) {
      std::cout << "PortAudio error: " << Pa_GetErrorText(error) << std::endl;
    }
  }

  for (auto stream_data : stream_datas_) {
    delete stream_data;
  }
}

} // namespace input
} // namespace taylortrack