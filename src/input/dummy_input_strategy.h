#ifndef TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
#define TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
#include "input_strategy.h"
namespace taylortrack {
    namespace input {
        class DummyInputStrategy: public InputStrategy {
        public:
            const char* read();
        };
    }
}
#endif // TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
