/**
* @file
* @brief Header file for the configuration file parser.
* @version 1
*/
#ifndef TAYLORTRACK_CONFIG_PARSER_H
#define TAYLORTRACK_CONFIG_PARSER_H

#include <fstream>
#include <iostream>
#include "config.h"
#include <sstream>

namespace taylortrack {
  namespace utils {
    /**
     * @class ConfigParser
     * @brief Parses a configuration and stores the configuration at its representative struct.
    */
    class ConfigParser {
     private:

      std::ifstream file_;
      std::string trim(const std::string &s);
      std::vector<std::string> split(const std::string &s, char delim);
      Options options;
      Audio audio;
      Video video;
      Combination combination;
      bool valid;
      void parse_file();


     public:
      /**
       * @brief Configuration parser constructor
       * Opens the supplied configuration file and parses it.
       * @param file_name Path to the file to be parsed.
      */
      ConfigParser(const char *file_name);
    };
  }
}

#endif //TAYLORTRACK_CONFIG_PARSER_H
