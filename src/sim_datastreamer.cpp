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
        taylortrack::input::WaveInputStrategy dummy = taylortrack::input::WaveInputStrategy(parameters);
        taylortrack::sim::Streamer streamer = taylortrack::sim::Streamer(&dummy, parameters.outport);
        streamer.start_streaming(parameters.inport);
        return EXIT_SUCCESS;
    }
}
