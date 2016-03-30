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
 * @brief Implementation of the streamer.h
 */

#include "sim/streamer.h"
#include <unistd.h>

namespace taylortrack {
namespace sim {
Streamer::Streamer(taylortrack::input::InputStrategy *strategy,
                   const char *outport) {
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
      strategy_->read(&output);
      out_port.write(true);  // blocking statement
    }  // while
    return true;
  }  // if
}

}  // namespace sim
}  // namespace taylortrack
