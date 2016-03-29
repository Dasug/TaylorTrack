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
* @brief Header file for taylortrack::input::WaveInputStrategy class.
*/

#ifndef TAYLORTRACK_INPUT_WAVE_INPUT_STRATEGY_H_
#define TAYLORTRACK_INPUT_WAVE_INPUT_STRATEGY_H_

#include <yarp/os/all.h>
#include "input/input_strategy.h"
#include "utils/config_parser.h"
#include "utils/parameters.h"
#include "utils/wave_parser.h"


namespace taylortrack {
namespace input {
/**
* @class WaveInputStrategy
* @brief Reads a wave file and processes it to a format readable by the tracking algorithm.
*
* Returns a YARP bottle consisting of sample amplitude levels as float values
* @warning Only supports Wave files with 16 Bits per sample at the moment!
*/
class WaveInputStrategy : public InputStrategy {
 public:
  WaveInputStrategy() = default;

  /**
   * @brief Default Copy constructor
   */
  WaveInputStrategy(const WaveInputStrategy &that) = default;

  /**
  * @brief ~WaveInputStrategy Destructor
  *
  * Releases file pointer, frees memory
  */
  ~WaveInputStrategy();

  /**
  * @brief Reads samples from the input file
  *
  * Number of samples to be read for every audio channel is defined in the taylortrack::utils::Parameters struct given to the constructor
  * @param bottle YARP bottle to store the read data
  * @pre is_done() returns false
  * @return YARP bottle consisting of sample amplitude levels as float values
  * @see is_done()
  */
  yarp::os::Bottle read(yarp::os::Bottle *bottle) override;

  /**
  * @brief Detects if the read method is done with reading the simulation data.
  * @return Status of the read method.
  */
  bool is_done() override;

  void set_parameters(const taylortrack::utils::Parameters &parameters) override;

  void set_config(const taylortrack::utils::ConfigParser &config_parser) override;

 private:
  taylortrack::utils::Parameters parameter_;
  taylortrack::utils::WaveParser *waveParser_ = nullptr;
  bool error_ = false;
};
}  // namespace input
}  // namespace taylortrack

#endif  // TAYLORTRACK_SRC_INPUT_WAVE_INPUT_STRATEGY_H_
