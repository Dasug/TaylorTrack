/**
* @file
* @brief Implementation of taylortrack::input::WaveInputStrategy class.
* @version 1
*/

#include "wave_input_strategy.h"

bool taylortrack::input::WaveInputStrategy::is_done() {
  if(waveParser_)
    return waveParser_->is_done();
  else
    return true;
}

taylortrack::input::WaveInputStrategy::~WaveInputStrategy() {
  if(this->waveParser_)
    delete this->waveParser_;
}

yarp::os::Bottle taylortrack::input::WaveInputStrategy::read(yarp::os::Bottle &bottle) {
  if (waveParser_ && waveParser_->is_valid() && !waveParser_->is_done()) {
    unsigned long sample_amount;
    if (parameter_.size <= 0) {
      sample_amount = waveParser_->get_sample_num();
    } else {
      sample_amount = (unsigned long) parameter_.size;
    }
    std::string samples = waveParser_->get_samples(sample_amount);
    long sampleNum = samples.size() / (waveParser_->get_bits_per_sample() / 8);
    long sampleSize = waveParser_->get_block_align() / waveParser_->get_num_channels();

    // Convert to Floats, change endian
    for (int i = 0; i < sampleNum; ++i) {
      long long temp = 0;
      for (int j = waveParser_->get_bits_per_sample() - 8; j >= 0; j -= 8) {
        long samplePosition = i * sampleSize + (j / 8);
        long long sample = samples[samplePosition];
        long long shift_distance = j;
        temp |= (sample << shift_distance);
      }
      float cfloat = (float) temp / 32767.0f;
      bottle.addDouble((double) cfloat);
    }
  }
  return bottle;
}
void taylortrack::input::WaveInputStrategy::set_parameters(taylortrack::utils::Parameters &params) {
  this->parameter_ = params;
  this->waveParser_ = new taylortrack::utils::WaveParser(params.file);
}
void taylortrack::input::WaveInputStrategy::set_config(taylortrack::utils::ConfigParser &config_parser) {
  // ignored for now
}
