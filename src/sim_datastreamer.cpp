/**
 * @file
 * @brief General data streamer main file
 */


#include "input/input_strategy.h"
#include "input/dummy_input_strategy.h"
#include "input/read_file_input_strategy.h"
#include "sim/streamer.h"
#include "utils/parameter_parser.h"
#include "input/wave_input_strategy.h"
#include "utils/config_parser.h"

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
        taylortrack::input::DummyInputStrategy strategy;
#elif defined INPUT_READ_FILE
        taylortrack::input::ReadFileInputStrategy strategy;
#elif defined INPUT_WAVE_FILE
        taylortrack::input::WaveInputStrategy strategy;
#else
#error Missing or unknown input strategy
#endif
        taylortrack::utils::ConfigParser parser = taylortrack::utils::ConfigParser("../conf/input.conf");
        if(parser.is_valid()) {
          strategy.set_parameters(parameters);
          strategy.set_config(parser);
          taylortrack::sim::Streamer streamer = taylortrack::sim::Streamer(&strategy, parameters.outport);
          streamer.start_streaming(parameters.inport);
          return EXIT_SUCCESS;
        } else {
          std::cout << "Config file could not be parsed!" << std::endl;
          return EXIT_FAILURE;
        }
    }
}
