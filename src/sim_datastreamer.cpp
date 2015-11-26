#include <yarp/os/all.h>
#include <iostream>
#include "input/input_strategy.h"
#include "input/dummy_input_strategy.h"
#include "input/read_file_input_strategy.h"

#include "sim/streamer.h"

int main(int argc, char *argv[]) {
    taylortrack::input::ReadFileInputStrategy dummy = taylortrack::input::ReadFileInputStrategy("./unnamed.jpg");
    taylortrack::sim::Streamer streamer = taylortrack::sim::Streamer(&dummy, "/bp39_out");
    streamer.start_streaming("/bp39_in");
    return 0;
}
