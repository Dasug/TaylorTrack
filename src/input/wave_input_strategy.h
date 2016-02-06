//
// Created by dasug on 06.02.16.
//

#ifndef TAYLORTRACK_WAVE_INPUT_STRATEGY_H
#define TAYLORTRACK_WAVE_INPUT_STRATEGY_H

#include "input_strategy.h"
#include "../utils/parameters.h"
#include "../utils/wave_parser.h"
#include <yarp/os/all.h>

namespace taylortrack {
    namespace input {
        class WaveInputStrategy : public InputStrategy {
        private:
            taylortrack::utils::Parameters parameter_;
            taylortrack::utils::WaveParser *waveParser;
            bool done_;
        public:
            /**
            * @brief ReadFileInputStrategy Constructor
            *
            * Opens the input stream and initialise
            * @param file_name Path to the file to be read.
            */
            WaveInputStrategy(taylortrack::utils::Parameters& params);

            /**
            * @brief Reads the entire file and returns the data.
            * @pre Should only be called if is_done() returns false
            * @return Simulation data.
            * @see is_done()
            */
            yarp::os::Bottle read();

            /**
            * @brief Detects if the read method is done with reading the simulation data.
            * @return Status of the read method.
            */
            bool is_done();

            /**
            * @ReadFileInputStrategy Destructor
            *
            * Frees up memory.
            */
            ~WaveInputStrategy();
        };
    }
}


#endif //TAYLORTRACK_WAVE_IMPUT_STRATEGY_H
