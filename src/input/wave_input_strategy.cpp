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
* @brief Implementation of taylortrack::input::WaveInputStrategy class.
* @version 1
*/

#include "input/wave_input_strategy.h"
#include <string>

namespace taylortrack {
namespace input {

bool WaveInputStrategy::is_done() {
  if (waveParser_)
    return error_ || waveParser_->is_done();
  else
    return true;
}

WaveInputStrategy::~WaveInputStrategy() {
  if (this->waveParser_)
    delete this->waveParser_;
}

yarp::os::Bottle
taylortrack::input::WaveInputStrategy::read(yarp::os::Bottle &bottle) {
  if (waveParser_ && waveParser_->is_valid() && !waveParser_->is_done()) {
    if (waveParser_->get_bits_per_sample() == 16) {
      int64_t sample_amount;
      if (parameter_.size <= 0) {
        sample_amount = waveParser_->get_sample_num();
      } else {
        sample_amount = parameter_.size;
      }
      std::string samples = waveParser_->get_samples(sample_amount);
      int64_t sampleNum = samples.size()
          / (waveParser_->get_bits_per_sample() / 8);
      int64_t sampleSize = waveParser_->get_block_align()
          / waveParser_->get_num_channels();

      // Convert to Floats, change endian
      for (int i = 0; i < sampleNum; ++i) {
        int16_t temp = 0;
        for (int j = waveParser_->get_bits_per_sample() - 8; j >= 0; j -= 8) {
          int64_t samplePosition = i * sampleSize + (j / 8);
          int64_t sample = static_cast<unsigned char>(samples[samplePosition]);
          int64_t shift_distance = j;
          temp |= (sample << shift_distance);
        }
        double cfloat = temp / 32767.0;
        bottle.addDouble(cfloat);
      }
    } else {
      std::cout <<
          "Currently only wave files with 16 bits per sample are supported!"
          << std::endl;
      this->error_ = true;
    }
  }
  return bottle;
}

void WaveInputStrategy::set_parameters(const utils::Parameters &params) {
  parameter_ = params;
  waveParser_ = new taylortrack::utils::WaveParser(params.file);
  error_ = false;
}

void WaveInputStrategy::set_config(const utils::ConfigParser &config_parser) {
  // ignored for now
}

}  // namespace input
}  // namespace taylortrack
