/**
 * @file
 * @brief Simulation for streaming data
 */


#include "input/input_strategy.h"
#include "input/dummy_input_strategy.h"
#include "input/read_file_input_strategy.h"
#include "sim/streamer.h"
#include "utils/parameter_parser.h"
#include "input/wave_input_strategy.h"

/**
 * @brief streaming data main method
 *
 * Reads a file with the Read_File_Input strategy and starts streaming the file
 */
int main(int argc, const char *argv[]) {
    taylortrack::utils::Parameters parameters = taylortrack::utils::ParameterParser::parse_streamer(argc,argv);
    if(!parameters.valid) {
        std::cout << "Invalid parameter usage. Please check --help" << std::endl;
        return EXIT_FAILURE;
    } else {
#if defined INPUT_DUMMY
        taylortrack::input::DummyInputStrategy strategy = taylortrack::input::DummyInputStrategy();
#elif defined INPUT_READ_FILE
        taylortrack::input::ReadFileInputStrategy strategy = taylortrack::input::ReadFileInputStrategy(parameters);
#elif defined INPUT_WAVE_FILE
        taylortrack::input::WaveInputStrategy strategy = taylortrack::input::WaveInputStrategy(parameters);
#else
#error Missing or unknown input strategy
#endif
        taylortrack::sim::Streamer streamer = taylortrack::sim::Streamer(&strategy, parameters.outport);
        streamer.start_streaming(parameters.inport);
        return EXIT_SUCCESS;
    }
}
