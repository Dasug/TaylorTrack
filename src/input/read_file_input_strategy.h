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
            * @brief ReadFileInputStrategy Constructor
            *
            * Opens the input stream and initialise
            * @param file_name Path to the file to be read.
            */
            ReadFileInputStrategy(const char* file_name);

            /**
            * @brief Reads the entire file and returns the data. 
            * @pre Should only be called if is_done() returns false
            * @return Simulation data.
            * @see is_done()
            */
            const char* read();

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
            ~ReadFileInputStrategy();

        private:
            bool done_;
            char* memblock_;
            std::streampos size_;
            std::ifstream* file_;
        };
    }
}
#endif // TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
