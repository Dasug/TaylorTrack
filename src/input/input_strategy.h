/**
* @file
* @brief Contains the input strategy interface.
* @details
* @version 1
*/
#ifndef TAYLORTRACK_INPUT_INPUT_STRATEGY_H_
#define TAYLORTRACK_INPUT_INPUT_STRATEGY_H_

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
      virtual void set_parameters(taylortrack::utils::Parameters &params) = 0;

      /**
       * @brief Sets configuration to be used for input strategy
       *
       * Might internally do more work to make sure new config is usable
       * @param config_parser taylortrack::utils::ConfigParser object. Provides strategy the configuration it needs.
       */
      virtual void set_config(taylortrack::utils::ConfigParser &config_parser) = 0;
    };
  } // namespace input
} // namespace taylortrack
#endif // TAYLORTRACK_INPUT_INPUT_STRATEGY_H_
