#include "read_file_input_strategy.h"
#include <fstream>
#include <iostream>

namespace taylortrack {
    namespace input {

        ReadFileInputStrategy::ReadFileInputStrategy(const char* file_name) {
            std::ifstream file (file_name, std::ios::in|std::ios::binary|std::ios::ate);
            
            if(file.is_open()) {         
                size_ = file.tellg();
                memblock_ = new char [size];
                file.seekg (0, std::ios::beg);
            }
            done_ = false;
        }

        const char* ReadFileInputStrategy::read() {
            if(file.is_open()) {
                file.read(memblock_,size_);
                file.close
            }
            done_ = true;
            return memblock_;
        }

        bool ReadFileInputStrategy::is_done() {
            delete[] memblock_;
            return done_;
        }

        ReadFileInputStrategy::~ReadFileInputStrategy() {
            delete[] memblock_;
        }
    }
}
