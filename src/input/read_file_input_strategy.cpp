/**
* @file
* @brief Implementation of the read_file_input_strategy.h
*/

#include "read_file_input_strategy.h"

namespace taylortrack {
    namespace input {
        ReadFileInputStrategy::ReadFileInputStrategy(const char* file_name) {
            file_ = new std::ifstream (file_name, std::ios::in|std::ios::binary|std::ios::ate);

            if(file_ -> fail()) {
              file_ -> close();
            }

            // Determine the size of the file and initialise the char array for the data..
            if(file_->is_open()) {
                size_ = (long) file_->tellg();
                file_->seekg(0, std::ios::beg);
            }
            done_ = false;
        }

        yarp::os::Bottle ReadFileInputStrategy::read(yarp::os::Bottle& bottle) {
            if(file_->is_open() && (size_ >= 0) ) {
                char *memblock = new char[size_];
                file_->read(memblock,size_);
                bottle.addString(yarp::os::ConstString(memblock, size_));
                file_->close();
            }
            done_ = true;
            return bottle;
        }

        bool ReadFileInputStrategy::is_done() {
            return done_;
        }

        ReadFileInputStrategy::~ReadFileInputStrategy() {
            delete file_;
        }
    }
}
// LCOV_EXCL_BR_STOP
