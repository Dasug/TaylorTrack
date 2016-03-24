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
* @brief Dummy Input for reading
* @details Implements a reading strategy input. This return a positive feedback if connection could be established.
* @version 1
*/
#ifndef TAYLORTRACK_SRC_INPUT_DUMMY_INPUT_STRATEGY_H_
#define TAYLORTRACK_SRC_INPUT_DUMMY_INPUT_STRATEGY_H_
#include <stdbool.h>
#include "input_strategy.h"
#include "utils/config_parser.h"
#include "utils/parameters.h"
namespace taylortrack {
namespace input {
/**
* @class DummyInputStrategy
* @brief Implements the dummy strategy.
*
* Strategy which streams the string: "Dummy Test successful".
*/
class DummyInputStrategy: public InputStrategy {
 public:
  /**
  * @brief DummyInputStrategy Constructor .
  *
  * Initialise done_.
  */
  DummyInputStrategy();

  /**
  * @brief Returns the test string.
  *
  * After the first call is_done will return true.
  * @param bottle YARP bottle to store the read data
  * @pre is_done() returns false
  * @return "Dummy Test successful"
  * @see is_done()
  */
  yarp::os::Bottle read(yarp::os::Bottle &bottle);

  /**
  * @brief Detects if the read method returned "Dummy Test successful".
  * @return Status of the read method.
  * @see read()
  */
  bool is_done();

  void set_parameters(const utils::Parameters &params);

  void set_config(const utils::ConfigParser &config_parser);

 private:
  bool done_;
};
}  // namespace input
}  // namespace taylortrack
#endif  // TAYLORTRACK_SRC_INPUT_DUMMY_INPUT_STRATEGY_H_
