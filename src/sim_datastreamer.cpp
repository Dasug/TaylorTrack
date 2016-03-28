/*
The MIT License (MIT)

Copyright (c) 2015 Marius Kaufmann, Tamara Frieß, Jannis Hoppe, Christian Hack

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file
 * @brief General data streamer main file
 */
#include "input/dummy_input_strategy.h"
#include "input/input_strategy.h"
#include "input/microphone_input_strategy.h"
#include "input/opencv_input_strategy.h"
#include "input/read_file_input_strategy.h"
#include "input/wave_input_strategy.h"
#include "sim/streamer.h"
#include "utils/parameter_parser.h"
#include "utils/config_parser.h"

/**
 * @brief streaming data main method
 *
 * Reads a file with the Read_File_Input strategy and starts streaming the file
 */
int main(int argc, const char *argv[]) {
    taylortrack::utils::Parameters parameters =
        taylortrack::utils::parameter_parser::parse_streamer(argc, argv);
    if (!parameters.valid) {
        std::cout << "Invalid parameter usage. Please check --help" << std::endl;
        return EXIT_FAILURE;
    } else {
#if defined INPUT_DUMMY
        taylortrack::input::DummyInputStrategy strategy;
#elif defined INPUT_READ_FILE
        taylortrack::input::ReadFileInputStrategy strategy;
#elif defined INPUT_WAVE_FILE
        taylortrack::input::WaveInputStrategy strategy;
#elif defined INPUT_OPENCV
        taylortrack::input::OpenCVInputStrategy strategy;
#elif defined INPUT_MICROPHONE
        taylortrack::input::MicrophoneInputStrategy strategy;
#else
#error Missing or unknown input strategy
#endif
        auto parser =
            taylortrack::utils::ConfigParser("../conf/input.conf");
        if (parser.is_valid()) {
          strategy.set_parameters(parameters);
          strategy.set_config(parser);
          auto streamer =
              taylortrack::sim::Streamer(&strategy, parameters.outport);
          streamer.start_streaming(parameters.inport);
          return EXIT_SUCCESS;
        } else {
          std::cout << "Config file could not be parsed!" << std::endl;
          return EXIT_FAILURE;
        }
    }
}
