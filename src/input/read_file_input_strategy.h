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
* @brief Contains the read input from file strategy.
* @details Constructor (and Destructor) to read and return data (with a specific strategy) and status of reading
* @version 1
*/

#ifndef TAYLORTRACK_SRC_INPUT_READ_FILE_INPUT_STRATEGY_H_
#define TAYLORTRACK_SRC_INPUT_READ_FILE_INPUT_STRATEGY_H_
#include <stdbool.h>
#include <fstream>
#include <iostream>
#include "input_strategy.h"
#include "../utils/parameters.h"
#include "../utils/config_parser.h"
namespace taylortrack {
namespace input {
/**
* @class ReadFileInputStrategy
* @brief Implements the read input from file strategy.
*
* Strategy which reads the simulation data from a given file and returns the entire file content at once.
*/
class ReadFileInputStrategy: public InputStrategy {
 public:
  /**
  * @brief Reads the entire file and returns the data.
  * @param bottle YARP bottle to store the read data
  * @pre Should only be called if is_done() returns false
  * @return Simulation data.
  * @see is_done()
  */
  yarp::os::Bottle read(yarp::os::Bottle &bottle);

  /**
  * @brief Detects if the read method is done with reading the simulation data.
  * @return Status of the read method.
  */
  bool is_done();

  void set_parameters(const utils::Parameters &params);

  void set_config(const utils::ConfigParser &config_parser);

  /**
  * @ReadFileInputStrategy Destructor
  *
  * Frees up memory.
  */
  ~ReadFileInputStrategy();

 private:
  bool done_ = true;
  int64_t size_, package_size_;
  std::ifstream *file_ = nullptr;
};
}  // namespace input
}  // namespace taylortrack
#endif  // TAYLORTRACK_SRC_INPUT_READ_FILE_INPUT_STRATEGY_H_
