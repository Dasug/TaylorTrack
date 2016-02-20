/**
* @file
* @brief Header file for taylortrack::input::WaveInputStrategy class.
* @version 1
*/

#ifndef TAYLORTRACK_WAVE_INPUT_STRATEGY_H
#define TAYLORTRACK_WAVE_INPUT_STRATEGY_H

#include "input_strategy.h"
#include <yarp/os/all.h>
#include "../utils/parameters.h"
#include "../utils/wave_parser.h"

namespace taylortrack {
  namespace input {
    /**
    * @class WaveInputStrategy
    * @brief Reads a wave file and processes it to a format readable by the tracking algorithm.
    *
    * Returns a YARP bottle consisting of sample amplitude levels as float values
    */
    class WaveInputStrategy: public InputStrategy {
     public:
      /**
      * @brief WaveInputStrategy Constructor
      *
      * Opens the input stream, parses the wave file header
      * @param params taylortrack::utils::Parameters object
      */
      WaveInputStrategy(taylortrack::utils::Parameters &params);

      /**
      * @brief Reads samples from the input file
      *
      * Number of samples to be read for every audio channel is defined in the taylortrack::utils::Parameters struct given to the constructor
      * @param bottle YARP bottle to store the read data
      * @pre is_done() returns false
      * @return YARP bottle consisting of sample amplitude levels as float values
      * @see is_done()
      */
      yarp::os::Bottle read(yarp::os::Bottle &bottle);

      /**
      * @brief Detects if the read method is done with reading the simulation data.
      * @return Status of the read method.
      */
      bool is_done();

      /**
      * @brief ~WaveInputStrategy Destructor
      *
      * Releases file pointer, frees memory
      */
      ~WaveInputStrategy();

     private:
      taylortrack::utils::Parameters parameter_;
      taylortrack::utils::WaveParser *waveParser_;
    };
  } // namespace input
} // namespace taylortrack


#endif //TAYLORTRACK_WAVE_IMPUT_STRATEGY_H
