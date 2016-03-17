/**
* @file
* @brief Contains the read input from file strategy.
* @details Constructor (and Destructor) to read and return data (with a specific strategy) and status of reading
* @version 1
*/

#ifndef TAYLORTRACK_INPUT_READ_FILE_INPUT_STRATEGY_H_
#define TAYLORTRACK_INPUT_READ_FILE_INPUT_STRATEGY_H_
#include <fstream>
#include <iostream>
#include <stdbool.h>
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

      void set_parameters(taylortrack::utils::Parameters &params);

      void set_config(taylortrack::utils::ConfigParser &config_parser);

      /**
      * @ReadFileInputStrategy Destructor
      *
      * Frees up memory.
      */
      ~ReadFileInputStrategy();

     private:
      bool done_ = true;
      long size_, package_size_;
      std::ifstream *file_ = nullptr;
      taylortrack::utils::Parameters params_;
    };
  } // namespace input
} // namesapace taylortrack
#endif // TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
