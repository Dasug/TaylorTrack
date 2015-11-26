#ifndef TAYLORTRACK_INPUT_READ_FILE_INPUT_STRATEGY_H_
#define TAYLORTRACK_INPUT_READ_FILE_INPUT_STRATEGY_H_
#include <stdbool.h>
#include "input_strategy.h"
namespace taylortrack {
    namespace input {
        class ReadFileInputStrategy: public InputStrategy {
        public:
            ReadFileInputStrategy(const char* file);
            const char* read();
            bool is_done();

        private:
            bool done_;
        };
    }
}
#endif // TAYLORTRACK_INPUT_DUMMY_INPUT_STRATEGY_H_
