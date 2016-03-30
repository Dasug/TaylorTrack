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
 * @brief Contains the header for the class taylortrack::input::MicrophoneInputStrategy
 * as well as the struct taylortrack::input::MicrophoneStreamData used within the class.
 */

#ifndef TAYLORTRACK_INPUT_MICROPHONE_INPUT_STRATEGY_H_
#define TAYLORTRACK_INPUT_MICROPHONE_INPUT_STRATEGY_H_

#include <portaudio.h>
#include <vector>
#include "input/input_strategy.h"
namespace taylortrack {
namespace input {
/**
 * @brief Contains some necessary data for a recording device and stores its audio samples
 */
struct MicrophoneStreamData {
  /**
   * @var values
   * A vector of vectors containing the recorded sample for each channel
   */
  std::vector<std::vector<double>> values;

  /**
   * @var channel_number
   * Number of channels on which this device is recording
   */
  int channel_number = 0;

  /**
   * @var has_written
   * Determines whether data has alsready been written into the values vectors.
   * Values should only be written into when has_written is false and only be read when has_written is true.
   * Otherwise it might cause race-conditions.
   */
  bool has_written = false;
};

/**
 * @class MicrophoneInputStrategy
 * @brief Records Audio using the PortAudio Library
 *
 * @code
 * // Example usage:
 * // initialize a parameter object using default values
 * taylortrack::utils::Parameters params;
 * // initialize default configuration object
 * taylortrack::utils::MicrophoneInputSettings input_settings;
 * // Create microphone device
 * taylortrack::utils::MicrophoneDevice device;
 * device.microphone_id = 2; // use your respective microphone id
 * input_settings.devices.push_back(device);
 * // Initialize Config parser on default values
 * taylortrack::utils::ConfigParser config;
 * // Apply Microphone settings
 * config.set_microphone_input_settings(input_settings);
 *
 * // afterwards you can initialize the strategy with the parameter and settings objects and start to read data as following
 * taylortrack::input::MicrophoneInputStrategy strategy;
 * strategy.set_parameters(params);
 * strategy.set_config(config);
 * yarp::os::Bottle bottle;
 * strategy.read(&bottle);
 * for (int i = 0; i < bottle.size(); i++) {
 *  std::cout << bottle.get(i).asDouble() << std::endl;
 * }
 * @endcode
*/
class MicrophoneInputStrategy : public InputStrategy {
 public:
  /**
   * @brief Constructor
   *
   * Initializes PortAudio and displays available audio input devices
  */
  MicrophoneInputStrategy();

  /**
   * @brief Default Copy constructor
   * @param that object that is copied
   */
  MicrophoneInputStrategy(const MicrophoneInputStrategy &that) = default;

  /**
   * @brief Destructor
   *
   * Frees memory and terminates PortAudio
  */
  virtual ~MicrophoneInputStrategy();
  /**
   * @brief Read data to be streamed.
   *
   * Will add sample values as doubles to the bottle. Each channel will write one sample in turns
   * until each channel has written the amount of samples specified when calling set_config.
   * @param bottle yarp::os::Bottle to write data into
   * @return Bottle supplied by parameter
   */
  yarp::os::Bottle read(yarp::os::Bottle *bottle) override;
  bool is_done() override;
  void set_parameters(const utils::Parameters &params) override;

  void set_config(const utils::ConfigParser &config_parser) override;

 private:
  // signals if all data has been transfered/read
  bool done_ = false;
  // Portaudio error
  PaError error_ = paNoError;
  // a struct containing all microphone devices
  // the sample rate and length of the frame
  utils::MicrophoneInputSettings settings_;
  // a vector containing all microphones with their
  // specific parameters such as ID, delay and number of channels
  std::vector<utils::MicrophoneDevice> microphone_devices_;
  // a vector of microphonestreamdata structs where
  // each entry contains the recorded samples
  std::vector<MicrophoneStreamData*> stream_datas_;
  // number of channels in the transmitted data
  int channels_ = 0;
  // a vector of portaudio streams for all microphones
  std::vector<PaStream*> streams_;
  // signals if data is currently being transmitted
  bool running_ = false;
};
}  // namespace input
}  // namespace taylortrack

#endif  // TAYLORTRACK_INPUT_MICROPHONE_INPUT_STRATEGY_H_
