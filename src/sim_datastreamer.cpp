/**
 * @file
 * @brief Simulation for streaming data
 */


#include <yarp/os/all.h>
#include <iostream>
#include "input/input_strategy.h"
#include "input/dummy_input_strategy.h"
#include "input/read_file_input_strategy.h"
#include "sim/streamer.h"
/**
 * @brief streaming data main method
 *
 * Reads a file with the Read_File_Input strategy and starts streaming the file
 */
int main(int argc, char *argv[]) {
    taylortrack::input::ReadFileInputStrategy dummy = taylortrack::input::ReadFileInputStrategy("/home/christian/Videos/Test.txt");
    taylortrack::sim::Streamer streamer = taylortrack::sim::Streamer(&dummy, "/bp39_out");
    streamer.start_streaming("/bp39_in");
    return 0;
}
