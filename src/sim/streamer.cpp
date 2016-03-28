/**
 * @file
 * @brief Implementation of the streamer.h
 */

#include "streamer.h"
#include <unistd.h>

namespace taylortrack {
  namespace sim {
    Streamer::Streamer(taylortrack::input::InputStrategy *strategy, const char *outport) {
      strategy_ = strategy;
      outport_ = outport;
    }

    bool Streamer::start_streaming(const char *inport) {
      if (strategy_->is_done()) {
        return false;
      } else {
        // Initialize YARP Network
        yarp::os::Network yarp;
        yarp::os::BufferedPort<yarp::os::Bottle> out_port;
        out_port.open(outport_);

        yarp.connect(out_port.getName(), yarp::os::ConstString(inport));
        while (!strategy_->is_done()) {
          usleep(200000);
          yarp::os::Bottle &output = out_port.prepare();
          output.clear();
          strategy_->read(output);
          out_port.write(true); //blocking statement
        } // while
        return true;
      } // if
    }

  } // namespace sim
} // namespace taylortrack
