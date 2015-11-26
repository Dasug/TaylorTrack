#include "read_file_input_strategy.h"
#include <fstream>
#include <iostream>

namespace taylortrack {
    namespace input {

        ReadFileInputStrategy::ReadFileInputStrategy() {
            done_ = false;
        }
        const char* ReadFileInputStrategy::read(const char* file) {
            done_ = true;
            return "Dummy Test successful";
        }

        bool ReadFileInputStrategy::is_done() {
            return done_;
        }
    }
}
