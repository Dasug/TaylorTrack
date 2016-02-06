/**
* @file
* @brief Dummy Input for reading
* @details Implements a reading strategy input. This return a positive feedback if connection could be established.
* @version 1
*/
#ifndef TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
#define TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
#include <stdbool.h>
#include "input_strategy.h"
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
            * @return "Dummy Test successful"
            * @see is_done()
            */
            yarp::os::Bottle read();

            /**
            * @brief Detects if the read metod returned "Dummy Test successful".
            * @return Status of the read method.
            * @see read()
            */
            bool is_done();

        private:
            bool done_;
        };
    }
}
#endif // TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
