#include "microphone_input_strategy.h"

namespace taylortrack {
namespace input {

yarp::os::Bottle MicrophoneInputStrategy::read(yarp::os::Bottle &bottle) {
  // TODO: Make it actually do something
  return yarp::os::Bottle();
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
    for (auto device : microphone_devices_) {
      if(device.microphone_id <= devices) {
        const PaDeviceInfo* current_device = Pa_GetDeviceInfo(device.microphone_id);
        std::cout << "Found device " << device.microphone_id << ": "
                  << current_device->name << std::endl;
        std::cout << "    " << current_device->maxInputChannels << " channels, "
                  << "delay: " << device.delay << " samples" << std::endl;
        channels_ += current_device->maxInputChannels;
      } else {
        std::cout << "Error: Microphone device " << device.microphone_id
                  << " could not be located!" << std::endl;
        done_ = true;
      }
    }

    if(!done_) {
      std::cout << "Channels in total: " << channels_ << std::endl;
    }
  } else {
    std::cout << "Error: No microphones defined!" << std::endl;
    done_ = true;
  }
   done_ = true;// debug thing
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
}

} // namespace input
} // namespace taylortrack