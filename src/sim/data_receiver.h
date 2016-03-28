#ifndef TAYLORTRACK_SIM_DATA_RECEIVER_H_
#define TAYLORTRACK_SIM_DATA_RECEIVER_H_

#include <yarp/os/all.h>
#include "utils/config.h"

namespace taylortrack {
namespace sim {
template <typename T> class DataReceiver {
 public:

  ~DataReceiver() {
    if(buffered_port_)
      delete buffered_port_;
  };

  bool init(const taylortrack::utils::CommunicationSettings &in_settings) {
    this->in_settings_ = in_settings;
    this->buffered_port_ = new yarp::os::BufferedPort<T>();
    return buffered_port_->open(in_settings.port);
  }

  T* read_data(bool blocking = true) const {
    T* input = buffered_port_->read(blocking);

    return input;
  };

 private:
  taylortrack::utils::CommunicationSettings in_settings_;
  yarp::os::Network yarp_;
  yarp::os::BufferedPort<T> *buffered_port_ = nullptr;
};
}  // namespace sim
}  // namespace taylortrack

#endif //TAYLORTRACK_SIM_DATA_RECEIVER_H_
