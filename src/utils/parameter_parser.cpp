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
 * @brief Parser
 */
#include "utils/parameter_parser.h"
#include <iostream>

taylortrack::utils::Parameters
taylortrack::utils::ParameterParser::parse_streamer(int argc,
                                                    const char **argv) {
  char *end;
  Parameters parameters = utils::Parameters();

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
        // stream buffer size
        case 's':
          if (++i >= argc) {
            parameters.valid = false;
          } else {
            parameters.size =  static_cast<int>(strtol(argv[i], &end, 10));
          }
          break;
        // Output port
        case 'o':
          if (++i >= argc) {
            parameters.valid = false;
          } else {
            parameters.outport = argv[i];
          }
          break;
        // Input port
        case 'i':
          if (++i >= argc) {
            parameters.valid = false;
          } else {
            parameters.inport = argv[i];
          }
          break;

        default:
          parameters.valid = false;
      }
    } else {
      parameters.file = argv[i];
      parameters.valid = true;
    }
  }
  return parameters;
}  // LCOV_EXCL_BR_LINE
