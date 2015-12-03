/**
* @file
* @brief Implementation of the dummy_input_strategy.h
*/

#include "dummy_input_strategy.h"
#include <stdbool.h>

namespace taylortrack {
    namespace input {
        DummyInputStrategy::DummyInputStrategy() {
            done_ = false;
        }
        const char* DummyInputStrategy::read() {
            done_ = true;
            return "Dummy Test successful";
        }

        bool DummyInputStrategy::is_done() {
            return done_;
        }
    }
}
