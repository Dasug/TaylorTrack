 #ifndef TAYLORTRACK_SIM_STREAMER_H_
 #define TAYLORTRACK_SIM_STREAMER_H_
 #include <stdbool.h>
 #include "../input/input_strategy.h"

 namespace taylortrack {
    namespace sim {
        class Streamer {
        private:

        public:
            Streamer(taylortrack::input::InputStrategy* strategy, const char* outport);
            bool start_streaming(const char* inport);

        private:
            taylortrack::input::InputStrategy* strategy_;
            const char *outport_;
        };
    } // namespace sim
 } // namespace taylortrack
 #endif // TAYLORTRACK_SIM_STREAMER_H_

