#include "data_receiver.h"
namespace taylortrack{
namespace sim{
DataReceiver::DataReceiver(const taylortrack::utils::CommunicationSettings &in_settings) {
  this->in_settings_ = in_settings;
  this->buffered_port_ = new yarp::os::BufferedPort<yarp::os::Bottle>();
  buffered_port_->open(in_settings.port);
}

std::vector<double> DataReceiver::readData(bool blocking) const {
  std::vector<double> return_vector;

  yarp::os::Bottle *input = buffered_port_->read(blocking);
  int size = 0;
  if (input && !input->isNull()) {
    size = input->size();
  }

  for (int i = 0; i < size; ++i) {
    return_vector.push_back(input->get(i).asDouble());
  }
  return return_vector;
}

DataReceiver::~DataReceiver() {
  delete buffered_port_;
}
}  // namespace sim
}  // namespace taylortrack

