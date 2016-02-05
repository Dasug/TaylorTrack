/**
 * @file
 * @brief Parser
 */
#include <iostream>
#include "parameter_parser.h"

Parameters taylortrack::utils::ParameterParser::parse_streamer(int argc,const char **argv) {
  char *end;
  Parameters parameters;

  for(int i = 1; i < argc; i++) {
    if(argv[i][0] == '-') {
      switch(argv[i][1]) {
        // stream buffer size
        case 's':
          if(++i >= argc) {
            parameters.valid = false;
          } else {
            parameters.size =  (int) strtol(argv[i], &end, 10);
          }
          break;
        // Output port
        case 'o':
          if(++i >= argc) {
            parameters.valid = false;
          } else {
            parameters.outport = argv[i];
          }
          break;
        // Input port
        case 'i':
          if(++i >= argc) {
            parameters.valid = false;
          } else {
            parameters.inport = argv[i];
          }
          break;

        default:
          parameters.valid = false;
      }
    }else {
      parameters.file = argv[i];
      parameters.valid = true;
    }
  }
  return parameters;
} // LCOV_EXCL_BR_LINE
