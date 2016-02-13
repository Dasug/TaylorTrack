#include "data_receiver.h"

taylortrack::sim::DataReceiver::DataReceiver(const taylortrack::utils::CommunicationSettings &in_settings) {
    this->in_settings = in_settings;
    this->port = new yarp::os::BufferedPort<yarp::os::Bottle>();
    port->open(in_settings.port);
}

std::vector<double> taylortrack::sim::DataReceiver::readData() const {
    std::vector<double> return_vector;

    yarp::os::Bottle *input = port->read(false);
    int size = 0;
    if(input && !input->isNull()) {
        size = input->size();
    }

    for (int i = 0; i < size; ++i) {
        return_vector.push_back(input->get(i).asDouble());
    }

    return return_vector;
}

taylortrack::sim::DataReceiver::~DataReceiver() {
    delete port;
}
