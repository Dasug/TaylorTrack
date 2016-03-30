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
 * @brief Handles Streaming
 */
#ifndef TAYLORTRACK_SIM_STREAMER_H_
#define TAYLORTRACK_SIM_STREAMER_H_
#include <stdbool.h>
#include "input/input_strategy.h"

namespace taylortrack {
namespace sim {
/**
 * @brief Starts streaming with specific strategy
 * @code
 * // Example usage:
 * // first initialize a streamer object with its output port and an input strategy
 * taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
 * taylortrack::sim::Streamer streamer(&dummy, "/test_out");
 *
 * // afterwards you can read in data into the strategy and start streaming it by assigning a
 * // port from which one can retrieve the streamed data
 * yarp::os::Bottle bottle;
 * dummy.read(&bottle);
 * streamer.start_streaming("/test_in");
 * @endcode
 */
class Streamer {
 public:
  /**
   * @brief Streamer Constructor
   *
   * @param strategy defines which strategy to use for streaming
   * @param outport write port (for connecting with readport)
   */
  Streamer(taylortrack::input::InputStrategy *strategy, const char *outport);
  /**
   * @brief starts streaming
   *
   * @param inport to retrieve all streamed data
   * @return true if streaming is done
   * @see start_streaming()
   */
  bool start_streaming(const char *inport);

 private:
  // an implementation of the input strategy
  taylortrack::input::InputStrategy *strategy_;
  // the yarp port to which the data has to be streamed
  const char *outport_;
  // the default copy constructor
  Streamer(const Streamer &that) = delete;
};
}  // namespace sim
}  // namespace taylortrack
#endif  // TAYLORTRACK_SIM_STREAMER_H_

