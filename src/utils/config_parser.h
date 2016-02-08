
#ifndef TAYLORTRACK_CONFIG_PARSER_H
#define TAYLORTRACK_CONFIG_PARSER_H

#include <fstream>
#include <iostream>
#include "config.h"
#include <sstream>

namespace taylortrack {
  namespace utils {
    class ConfigParser {
     private:
      std::ifstream file_;
      std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
      std::vector<std::string> split(const std::string &s, char delim);
      std::string trim(const std::string &s);
      Options options;
      Audio audio;
      Video video;
      Combination combination;

     public:
      ConfigParser(const char *file_name);
      void parse_file();
    };
  }
}

#endif //TAYLORTRACK_CONFIG_PARSER_H
