/**
 * @file
 * @brief Parser
 */
#include <iostream>
#include "parameter_parser.h"
std::tuple<const char*, int, const char*, const char*, bool> taylortrack::utils::ParameterParser::parse_streamer(int argc,const char **argv) {
  char *end;
  const char *file;
  const char *outport = "/bp39_out";
  const char *inport = "/bp39_in";
  int size = 0;
  bool valid = false;

  for(int i = 1; i < argc; i++) {
    if(argv[i][0] == '-') {
      switch(argv[i][1]) {
        // stream buffer size
        case 's':
          if(++i >= argc) {
            valid = false;
          } else {
            size =  (int) strtol(argv[i], &end, 10);
          }
          break;
        // Output port
        case 'o':
          if(++i >= argc) {
            valid = false;
          } else {
            outport = argv[i];
          }
          break;
        // Input port
        case 'i':
          if(++i >= argc) {
            valid = false;
          } else {
            inport = argv[i];
          }
          break;

        default:
          valid = false;
      }
    }else {
      file = argv[i];
      valid = true;
    }
  }
  return std::make_tuple(file, size, outport, inport, valid);
} // LCOV_EXCL_BR_LINE
