#ifndef TAYLORTRACK_DATA_RECEIVER_H
#define TAYLORTRACK_DATA_RECEIVER_H

#include <yarp/os/all.h>
#include "utils/config.h"

namespace taylortrack {
  namespace sim {
    class DataReceiver {
     public:
      DataReceiver(const taylortrack::utils::CommunicationSettings &in_settings);
      ~DataReceiver();
      std::vector<double> readData(bool blocking = true) const;

     private:
      taylortrack::utils::CommunicationSettings in_settings_;
      yarp::os::Network yarp_;
      yarp::os::BufferedPort<yarp::os::Bottle> *buffered_port_;
    };
  } // namespace sim
} // namespace taylortrack

#endif //TAYLORTRACK_DATA_RECEIVER_H
