/**
 * @file
 * @brief Contains the header for the class taylortrack::input::MicrophoneInputStrategy
 * as well as the struct taylortrack::input::MicrophoneStreamData used within the class.
 */

#ifndef TAYLORTRACK_INPUT_MICROPHONE_INPUT_STRATEGY_H_
#define TAYLORTRACK_INPUT_MICROPHONE_INPUT_STRATEGY_H_

#include <portaudio.h>
#include "input_strategy.h"
namespace taylortrack {
namespace input {

/**
 * @Struct
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
   * @brief Destructor
   *
   * Frees memory and terminates PortAudio
  */
  virtual ~MicrophoneInputStrategy();
  virtual yarp::os::Bottle read(yarp::os::Bottle &bottle) override;
  virtual bool is_done() override;
  virtual void set_parameters(const utils::Parameters &params) override;
  virtual void set_config(const utils::ConfigParser &config_parser) override;

 private:
  bool done_ = false;
  PaError error_ = paNoError;
  utils::MicrophoneInputSettings settings_;
  std::vector<utils::MicrophoneDevice> microphone_devices_;
  std::vector<MicrophoneStreamData*> stream_datas_;
  int channels_ = 0;
  std::vector<PaStream*> streams_;
  bool running_ = false;
};
}  // namespace input
}  // namespace taylortrack


#endif //TAYLORTRACK_INPUT_MICROPHONE_INPUT_STRATEGY_H
