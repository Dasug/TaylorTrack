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
* @brief Contains the input strategy interface.
* @details
* @version 1
*/
#ifndef TAYLORTRACK_SRC_INPUT_INPUT_STRATEGY_H_
#define TAYLORTRACK_SRC_INPUT_INPUT_STRATEGY_H_

#include <yarp/os/all.h>
#include "../utils/parameters.h"
#include "../utils/config_parser.h"

namespace taylortrack {
namespace input {
/**
* @interface InputStrategy
* @brief Interface for the different input strategies.
*
* Strategy which will be used by the simulator to get the simulation data.
*/
class InputStrategy {
 public:
  /**
  * @brief Read data to be streamed.
  * @param bottle yarp::os::Bottle to write data into
  * @return Bottle supplied by parameter
  */
  virtual yarp::os::Bottle read(yarp::os::Bottle &bottle) = 0;

  /**
  * @brief Detects if the read metod is done with reading the simulation data.
  * @return Status of the read method.
  */
  virtual bool is_done() = 0;

  /**
   * @brief Sets console parameters to be used for input strategy
   *
   * Might internally do more work to make sure new parameters are usable
   * @param params parameters to be used
   */
  virtual void set_parameters(const utils::Parameters &params) = 0;

  /**
   * @brief Sets configuration to be used for input strategy
   *
   * Might internally do more work to make sure new config is usable
   * @param config_parser taylortrack::utils::ConfigParser object. Provides strategy the configuration it needs.
   */
  virtual void set_config(const utils::ConfigParser &config_parser) = 0;
};
}  // namespace input
}  // namespace taylortrack
#endif  // TAYLORTRACK_SRC_INPUT_INPUT_STRATEGY_H_
