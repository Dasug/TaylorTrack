/**
 * @file
 * @brief Simulation for streaming data
 */


#include "input/input_strategy.h"
#include "input/dummy_input_strategy.h"
#include "input/read_file_input_strategy.h"
#include "sim/streamer.h"
#include "utils/parameter_parser.h"
/**
 * @brief streaming data main method
 *
 * Reads a file with the Read_File_Input strategy and starts streaming the file
 */
int main(int argc, const char *argv[]) {
    int size;
    const char *file;
    bool valid;
    std::tie(file,size, valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,argv);
    if(!valid) {
        std::cout << "Invalid parameter usage. Please check --help" << std::endl;
        return EXIT_FAILURE;
    } else {
        taylortrack::input::ReadFileInputStrategy dummy = taylortrack::input::ReadFileInputStrategy(file);
        taylortrack::sim::Streamer streamer = taylortrack::sim::Streamer(&dummy, "/bp39_out");
        streamer.start_streaming("/bp39_in");
        return EXIT_SUCCESS;
    }
}
