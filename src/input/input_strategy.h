#ifndef TAYLORTRACK_INPUT_INPUT_STRATEGY_H_
#define TAYLORTRACK_INPUT_INPUT_STRATEGY_H_
namespace taylortrack {
    namespace input {
        class InputStrategy {
        public:
            virtual const char* read() = 0;
            virtual bool is_done() = 0;
        };
    } // namespace input
} // namespace taylortrack
#endif // TAYLORTRACK_INPUT_INPUT_STRATEGY_H_
