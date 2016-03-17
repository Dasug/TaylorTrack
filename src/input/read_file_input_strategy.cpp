/**
* @file
* @brief Implementation of the read_file_input_strategy.h
*/

#include "read_file_input_strategy.h"

namespace taylortrack {
  namespace input {

    yarp::os::Bottle ReadFileInputStrategy::read(yarp::os::Bottle &bottle) {
      if (file_ && file_->is_open() && file_->tellg() != size_) {
        char *memblock = new char[package_size_];
        file_->read(memblock, package_size_);
        bottle.addString(yarp::os::ConstString(memblock, package_size_));
        done_ = file_->eof() || file_->tellg() == size_;
      }else {
        done_ = true;
      }

      if(file_ && done_ && file_->is_open())
        file_->close();

      return bottle;
    }

    bool ReadFileInputStrategy::is_done() {
      return !file_ || done_;
    }

    ReadFileInputStrategy::~ReadFileInputStrategy() {
      if(file_)
        delete file_;
    }

    void ReadFileInputStrategy::set_parameters(taylortrack::utils::Parameters &params) {
      this->params_ = params;
      file_ = new std::ifstream(params.file, std::ios::in | std::ios::binary | std::ios::ate);

      if (file_->fail())
        file_->close();

      // Determine the size of the file and initialise the char array for the data..
      if (file_->is_open()) {
        size_ = (long) file_->tellg();
        file_->seekg(0, std::ios::beg);
        package_size_ = (params.size == 0) ? size_ : params.size;
        //params.size == 0 ? package_size_ = size_ : package_size_ = params.size;
      }

      done_ = false;
    }


    void ReadFileInputStrategy::set_config(taylortrack::utils::ConfigParser &config_parser) {
      // do nothing, we don't need the config right now.
    }
  } //namespace input
} // namespace taylortrack
// LCOV_EXCL_BR_STOP
