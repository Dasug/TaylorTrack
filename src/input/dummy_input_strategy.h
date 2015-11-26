#ifndef TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
#define TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
#include <stdbool.h>
#include "input_strategy.h"
namespace taylortrack {
    namespace input {
        class DummyInputStrategy: public InputStrategy {
        public:
            DummyInputStrategy();
            const char* read();
            bool is_done();

        private:
            bool done_;
        };
    }
}
#endif // TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
