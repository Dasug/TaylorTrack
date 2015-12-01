#include "read_file_input_strategy.h"
#include <fstream>
#include <iostream>

namespace taylortrack {
    namespace input {

        ReadFileInputStrategy::ReadFileInputStrategy(const char* file_name) {

            file_ = new std::ifstream (file_name, std::ios::in|std::ios::binary|std::ios::ate);

            if(file_->is_open()) {
                size_ = file_->tellg();
                memblock_ = new char [size_];
                file_->seekg(0, std::ios::beg);
            }
            done_ = false;
        }

        const char* ReadFileInputStrategy::read() {
            if(file_->is_open()) {
                file_->read(memblock_,size_);
                file_->close();
            }
            done_ = true;
            return memblock_;
        }

        bool ReadFileInputStrategy::is_done() {
            return done_;
        }

        ReadFileInputStrategy::~ReadFileInputStrategy() {
            delete[] memblock_;
            delete file_;
        }
    }
}
