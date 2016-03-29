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
     * @class Streamer
     * @brief Starts streaming with specific strategy
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
  } // namespace sim
} // namespace taylortrack
#endif // TAYLORTRACK_SIM_STREAMER_H_

