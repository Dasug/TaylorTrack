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
#include <vector>

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
      std::vector<std::string> split_microphones(std::string s);
      bool parse_file();
      Options options;
      Audio audio;
      Video video;
      Combination combination;
      bool valid;


     public:
      /**
       * @brief Configuration parser constructor
       * Opens the supplied configuration file and parses it.
       * @param file_name Path to the file to be parsed.
      */
      ConfigParser(const char *file_name);

      /**
      * @brief Gets the general configuration for the algorithms
      * @pre is_valid() returns true
      * @return General configuration for the algorithms
      */
      const Options get_general_configuration() const {
        return options;
      }

      /**
      * @brief Gets the configuration for the speaker tracking algorithm
      * @pre is_valid() returns true
      * @return Configuration for the speaker tracking algorithm
      */
      const Audio get_audio_configuration() const {
        return audio;
      }

      /**
      * @brief Gets the configuration for the vision tracking algorithm
      * @pre is_valid() returns true
      * @return Configuration for the vision tracking algorithm
      */
      const Video get_video_configuration() const {
        return video;
      }

      /**
      * @brief Gets the configuration for the combination algorithm
      * @pre is_valid() returns true
      * @return Configuration for the algorithm
      */
      const Combination get_combination_configuration() const {
        return combination;
      }

      /**
      * @brief Checks whether the configuration file is valid or not.
      * @return true if the configuration is valid, otherwise false
      */
      bool is_valid() const {
        return valid;
      }
    };
  }
}

#endif //TAYLORTRACK_CONFIG_PARSER_H
