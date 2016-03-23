#ifndef TAYLORTRACK_MICROPHONE_INPUT_STRATEGY_H_
#define TAYLORTRACK_MICROPHONE_INPUT_STRATEGY_H_

#include <portaudio.h>
#include "input_strategy.h"
namespace taylortrack {
namespace input {
class MicrophoneInputStrategy : public InputStrategy {
 public:
  MicrophoneInputStrategy();
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
  int channels_ = 0;
};
} // namespace input
} // namespace taylortrack


#endif //TAYLORTRACK_MICROPHONE_INPUT_STRATEGY_H
