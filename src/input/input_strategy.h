/**
* @file
* @brief Contains the input strategy interface.
*/
#ifndef TAYLORTRACK_INPUT_INPUT_STRATEGY_H_
#define TAYLORTRACK_INPUT_INPUT_STRATEGY_H_
namespace taylortrack {
    namespace input {
        /**
		* @interface InputStrategy
		* @brief Interface for the different input strategies.
		*
		* Strategy which will be used by the simulator to get the simulation data.
        */
        class InputStrategy {
        public:
        	/**
			* @brief Read data to be streamed.
			* @return Simulation data.
        	*/
            virtual const char* read() = 0;

            /**
            * @brief Detects if the read metod is done with reading the simulation data.
            * @return Status of the read method.
            */
            virtual bool is_done() = 0;
        };
    } // namespace input
} // namespace taylortrack
#endif // TAYLORTRACK_INPUT_INPUT_STRATEGY_H_
