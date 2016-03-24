/*
The MIT License (MIT)

Copyright (c) 2015 Marius Kaufmann, Tamara Frieß, Jannis Hoppe, Christian Hack

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
* @file
* @brief Implementation of the read_file_input_strategy.h
*/

#include "input/read_file_input_strategy.h"

namespace taylortrack {
namespace input {

yarp::os::Bottle ReadFileInputStrategy::read(yarp::os::Bottle &bottle) {
  if (file_ && file_->is_open() && file_->tellg() != size_) {
    char *memblock = new char[package_size_];
    file_->read(memblock, package_size_);
    bottle.addString(yarp::os::ConstString(memblock, package_size_));
    done_ = file_->eof() || file_->tellg() == size_;
  } else {
    done_ = true;
  }

  if (file_ && done_ && file_->is_open())
    file_->close();

  return bottle;
}

bool ReadFileInputStrategy::is_done() {
  return !file_ || done_;
}

ReadFileInputStrategy::~ReadFileInputStrategy() {
  if (file_)
    delete file_;
}

void ReadFileInputStrategy::set_parameters(const utils::Parameters &params) {
  file_ = new std::ifstream(params.file,
                            std::ios::in | std::ios::binary | std::ios::ate);

  if (file_->fail())
    file_->close();

  // Determine the size of the file and initialise the char array for the data..
  if (file_->is_open()) {
    size_ = static_cast<int64_t>(file_->tellg());
    file_->seekg(0, std::ios::beg);
    package_size_ = (params.size == 0) ? size_ : params.size;
  }

  done_ = false;
}

void ReadFileInputStrategy::set_config(
    const utils::ConfigParser &config_parser) {
  // do nothing, we don't need the config right now.
}
}  // namespace input
}  // namespace taylortrack
// LCOV_EXCL_BR_STOP
