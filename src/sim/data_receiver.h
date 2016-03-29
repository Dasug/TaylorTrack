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
 * @brief Contains the taylortrack::sim::DataReceiver template
 */

#ifndef TAYLORTRACK_SIM_DATA_RECEIVER_H_
#define TAYLORTRACK_SIM_DATA_RECEIVER_H_

#include <yarp/os/all.h>
#include "utils/config.h"

namespace taylortrack {
namespace sim {
/**
 * @brief Receives any type of data from a YARP buffered port and sends it back to the client
 *
 * Needs taylortrack::utils::CommunicationSettings to
 */
template <typename T> class DataReceiver {
 public:
  DataReceiver() = default;

  /**
   * @brief Destructor
   *
   * Frees memory and closes YARP connections
   */
  ~DataReceiver() {
    if (buffered_port_) {
      buffered_port_->close();
      delete buffered_port_;
    }
  }

  /**
   * @brief Init method
   *
   * Opens connection to a yarp port, needs to be called for the
   * @param in_settings incomming communication settings
   * @return true if initialization successful
   */
  bool init(const taylortrack::utils::CommunicationSettings &in_settings) {
    this->in_settings_ = in_settings;
    this->buffered_port_ = new yarp::os::BufferedPort<T>();
    return buffered_port_->open(in_settings.port);
  }

  /**
   * @brief checks whether object has been initialized
   *
   * @return true, if initialized
   */
  bool is_initialized() {
    return static_cast<bool>(buffered_port_);
  }

  /**
   * @brief Reads data from the YARP port
   * @param blocking Determines whether the read call for the buffered port
   * should be blocking or non-blocking
   * @return Pointer to read data. Can be Null Pointer in case of an error or if object has not been initialized
   */
  T* read_data(bool blocking = true) const {
    if (buffered_port_) {
      T* input = buffered_port_->read(blocking);
      return input;
    } else {
      return nullptr;
    }
  }

 private:
  taylortrack::utils::CommunicationSettings in_settings_;
  yarp::os::Network yarp_;
  yarp::os::BufferedPort<T> *buffered_port_ = nullptr;
  DataReceiver(const DataReceiver &that) = delete;
};
}  // namespace sim
}  // namespace taylortrack

#endif  // TAYLORTRACK_SIM_DATA_RECEIVER_H_
