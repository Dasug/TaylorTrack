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
    public:
      const CommunicationSettings &get_input_communication_out() const {
        return input_communication_out_;
      }

      const CommunicationSettings &get_audio_communication_in() const {
        return audio_communication_in_;
      }

      const CommunicationSettings &get_audio_communication_out() const {
        return audio_communication_out_;
      }

      const CommunicationSettings &get_video_communication_in() const {
        return video_communication_in_;
      }

      const CommunicationSettings &get_video_communication_out() const {
        return video_communication_out_;
      }

      const CommunicationSettings &get_combination_communication_in() const {
        return combination_communication_in_;
      }

      const CommunicationSettings &get_combination_communication_out() const {
        return combination_communication_out_;
      }

      const CommunicationSettings &get_visualizer_communication_in() const {
        return visualizer_communication_in_;
      }

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
      const GeneralOptions get_general_configuration() const {
        return general_options_;
      }

      /**
      * @brief Gets the configuration for the speaker tracking algorithm
      * @pre is_valid() returns true
      * @return Configuration for the speaker tracking algorithm
      */
      const AudioSettings get_audio_configuration() const {
        return audio_settings_;
      }

      /**
      * @brief Gets the configuration for the vision tracking algorithm
      * @pre is_valid() returns true
      * @return Configuration for the vision tracking algorithm
      */
      const VideoSettings get_video_configuration() const {
        return video_settings_;
      }

      /**
      * @brief Gets the configuration for the combination algorithm
      * @pre is_valid() returns true
      * @return Configuration for the algorithm
      */
      const CombinationSettings get_combination_configuration() const {
        return combination_settings_;
      }

      /**
      * @brief Checks whether the configuration file is valid or not.
      * @return true if the configuration is valid, otherwise false
      */
      bool is_valid() const {
        return valid_;
      }

     private:
      std::string trim(const std::string &s);
      std::vector<std::string> split(const std::string &s, char delim);
      std::vector<std::string> split_microphones(std::string s);
      bool parse_file();
      bool valid_;
      std::ifstream file_;
      GeneralOptions general_options_;
      AudioSettings audio_settings_;
      VideoSettings video_settings_;
      CombinationSettings combination_settings_;
      CommunicationSettings input_communication_out_,
                            audio_communication_in_,
                            audio_communication_out_,
                            video_communication_in_,
                            video_communication_out_,
                            combination_communication_in_,
                            combination_communication_out_,
                            visualizer_communication_in_;
    };
  }
}

#endif //TAYLORTRACK_CONFIG_PARSER_H
