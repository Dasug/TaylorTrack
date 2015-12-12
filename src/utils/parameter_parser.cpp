/**
 * @file
 * @brief Parser
 */
#include <iostream>
#include "parameter_parser.h"
std::tuple<const char*, int, bool> taylortrack::utils::ParameterParser::parse_streamer(int argc,const char **argv) {
  char *end;
  const char *file;
  int size = 0;
  bool valid = false;

  for(int i = 1; i < argc; i++) {
    if(argv[i][0] == '-') {
      if(argv[i][1] == 's') {
        if(++i >= argc) {
          valid = false;
        } else {
          size =  (int) strtol(argv[i], &end, 10);
        }
      }
    }else {
      file = argv[i];
      valid = true;
    }
  }
  return std::make_tuple(file, size, valid);
}
