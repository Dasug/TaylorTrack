#ifndef TAYLORTRACK_DATA_RECEIVER_H
#define TAYLORTRACK_DATA_RECEIVER_H

#include <yarp/os/all.h>
#include "../utils/config.h"

namespace taylortrack {
    namespace sim {
        class DataReceiver {
        private:
            taylortrack::utils::CommunicationSettings in_settings;
            yarp::os::Network yarp;
            yarp::os::BufferedPort<yarp::os::Bottle>* port;
        public:
            DataReceiver(const taylortrack::utils::CommunicationSettings& in_settings);
            ~DataReceiver();

            std::vector<double> readData(bool blocking = true) const;
        };
    }
}


#endif //TAYLORTRACK_DATA_RECEIVER_H
