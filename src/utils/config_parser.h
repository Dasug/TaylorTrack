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
* @brief Header file for the configuration file parser.
*/
#ifndef TAYLORTRACK_UTILS_CONFIG_PARSER_H_
#define TAYLORTRACK_UTILS_CONFIG_PARSER_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "utils/config.h"
namespace taylortrack {
namespace utils {
/**
 * @class ConfigParser
 * @brief Parses a configuration and stores the configuration at its representative struct.
*/
class ConfigParser {
 public:
  /**
 * @brief Configuration parser constructor
 * Opens the supplied configuration file and parses it.
 * @param file_name Path to the file to be parsed.
 */
  explicit ConfigParser(const char *file_name);

  /**
   * @brief Configuration parser constructor, uses only default values
  */
  ConfigParser();
  /**
   * @brief Retrieves the outgoing communication settings for the input module
   * @return taylortrack::utils::CommunicationSettings object, containing the outgoing communication settings for the input module
   * @sa taylortrack::input::InputStrategy
   */
  const CommunicationSettings &get_input_communication_out() const {
    return input_communication_out_;
  }

  /**
   * @brief Retrieves the incoming communication settings for the audio tracking module
   * @return taylortrack::utils::CommunicationSettings object, containing the incoming communication settings for the audio tracking module
   * @sa taylortrack::localization::Localizer
   */
  const CommunicationSettings &get_audio_communication_in() const {
    return audio_communication_in_;
  }

  /**
   * @brief Retrieves the outgoing communication settings for the audio tracking module
   * @return taylortrack::utils::CommunicationSettings object, containing the outgoing communication settings for the audio tracking module
   * @sa taylortrack::localization::Localizer
   */
  const CommunicationSettings &get_audio_communication_out() const {
    return audio_communication_out_;
  }

  /**
   * @brief Retrieves the incoming communication settings for the video tracking module
   * @return taylortrack::utils::CommunicationSettings object, containing the incoming communication settings for the video tracking module
   * @sa taylortrack::localization::Localizer
   */
  const CommunicationSettings &get_video_communication_in() const {
    return video_communication_in_;
  }

  /**
   * @brief Retrieves the outgoing communication settings for the video tracking module
   * @return taylortrack::utils::CommunicationSettings object, containing the outgoing communication settings for the video tracking module
   * @sa taylortrack::localization::Localizer
   */
  const CommunicationSettings &get_video_communication_out() const {
    return video_communication_out_;
  }

  /**
   * @brief Retrieves the incoming communication settings for the tracking combination module
   * @return taylortrack::utils::CommunicationSettings object, containing the incoming communication settings for the tracking combination module
   * @sa taylortrack::localization::Localizer
   */
  const CommunicationSettings &get_combination_communication_in() const {
    return combination_communication_in_;
  }

  /**
   * @brief Retrieves the outgoing communication settings for the tracking combination module
   * @return taylortrack::utils::CommunicationSettings object, containing the outgoing communication settings for the tracking combination module
   * @sa taylortrack::localization::Localizer
   */
  const CommunicationSettings &get_combination_communication_out() const {
    return combination_communication_out_;
  }

  /**
   * @brief Retrieves the incoming communication settings for the visualizer
   * @return taylortrack::utils::CommunicationSettings object, containing the incoming communication settings for the visualizer
   * @sa taylortrack::vis::OutputVisualizer
   */
  const CommunicationSettings &get_visualizer_communication_in() const {
    return visualizer_communication_in_;
  }

  /**
   * @brief Sets general options
   * @param general_options taylortrack::utils::GeneralOptions to be set
   */
  void set_general_options(const GeneralOptions &general_options) {
    ConfigParser::general_options_ = general_options;
  }

  /**
   * @brief Sets the settings for the audio tracking module
   * @param audio_settings taylortrack::utils::AudioSettings to be set
   * @sa taylortrack::localization::Localizer
   */
  void set_audio_settings(const AudioSettings &audio_settings) {
    ConfigParser::audio_settings_ = audio_settings;
  }

  /**
   * @brief Sets the settings for the video tracking module
   * @param video_settings taylortrack::utils::VideoSettings to be set
   * @sa taylortrack::localization::Localizer
   */
  void set_video_settings(const VideoSettings &video_settings) {
    ConfigParser::video_settings_ = video_settings;
  }

  /**
   * @brief Sets the settings for the tracking combination module
   * @param combination_settings taylortrack::utils::CombinationSettings to be set
   * @sa taylortrack::localization::Localizer
   */
  void set_combination_settings(const CombinationSettings &combination_settings) {
    ConfigParser::combination_settings_ = combination_settings;
  }

  /**
   * @brief Sets the outgoing communication settings for the input module
   * @param input_communication_out taylortrack::utils::CommunicationSettings to be set
   * @sa taylortrack::input::InputStrategy
   */
  void set_input_communication_out(
      const CommunicationSettings &input_communication_out) {
    ConfigParser::input_communication_out_ = input_communication_out;
  }

  /**
   * @brief Sets the incoming communication settings for the audio tracking module
   * @param audio_communication_in taylortrack::utils::CommunicationSettings to be set
   * @sa taylortrack::localization::Localizer
   */
  void set_audio_communication_in(
      const CommunicationSettings &audio_communication_in) {
    ConfigParser::audio_communication_in_ = audio_communication_in;
  }

  /**
   * @brief Sets the outgoing communication settings for the audio tracking module
   * @param audio_communication_out taylortrack::utils::CommunicationSettings to be set
   * @sa taylortrack::localization::Localizer
   */
  void set_audio_communication_out(
      const CommunicationSettings &audio_communication_out) {
    ConfigParser::audio_communication_out_ = audio_communication_out;
  }

  /**
   * @brief Sets the incoming communication settings for the video tracking module
   * @param video_communication_in taylortrack::utils::CommunicationSettings to be set
   * @sa taylortrack::localization::Localizer
   */
  void set_video_communication_in(
      const CommunicationSettings &video_communication_in) {
    ConfigParser::video_communication_in_ = video_communication_in;
  }

  /**
   * @brief Sets the outgoing communication settings for the video tracking module
   * @param video_communication_out taylortrack::utils::CommunicationSettings to be set
   * @sa taylortrack::localization::Localizer
   */
  void set_video_communication_out(
      const CommunicationSettings &video_communication_out) {
    ConfigParser::video_communication_out_ = video_communication_out;
  }

  /**
   * @brief Sets the incoming communication settings for the tracking combination module
   * @param combination_communication_in taylortrack::utils::CommunicationSettings to be set
   * @sa taylortrack::localization::Localizer
   */
  void set_combination_communication_in(
      const CommunicationSettings &combination_communication_in) {
    ConfigParser::combination_communication_in_ = combination_communication_in;
  }

  /**
   * @brief Sets the outgoing communication settings for the tracking combination module
   * @param combination_communication_out taylortrack::utils::CommunicationSettings to be set
   * @sa taylortrack::localization::Localizer
   */
  void set_combination_communication_out(
      const CommunicationSettings &combination_communication_out) {
    ConfigParser::combination_communication_out_
        = combination_communication_out;
  }

  /**
   * @brief Sets the incoming communication settings for the visualizer
   * @param visualizer_communication_in taylortrack::utils::CommunicationSettings to be set
   * @sa taylortrack::vis::OutputVisualizer
   */
  void set_visualizer_communication_in(
      const CommunicationSettings &visualizer_communication_in) {
    ConfigParser::visualizer_communication_in_ = visualizer_communication_in;
  }

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
   * @brief Sets the settings for the microphone input module
   * @param microphone_input_settings taylortrack::utils::MicrophoneInputSettings to be set
   * @sa taylortrack::input::MicrophoneInputStrategy
   */
  void set_microphone_input_settings(const MicrophoneInputSettings &microphone_input_settings) {
    ConfigParser::microphone_input_settings_ = microphone_input_settings;
  }

  /**
  * @brief Gets the configuration for the microphone input module
  * @pre is_valid() returns true
  * @return Configuration for the microphone input module
  */
  const MicrophoneInputSettings get_microphone_input_configuration() const {
    return microphone_input_settings_;
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

  ConfigParser(const ConfigParser &that) = delete;
 private:
  std::string trim(const std::string &temporary_string);
  std::vector<std::string> split(const std::string &temporary_string, char delimiter);
  std::vector<std::string> split_microphones(std::string temporary_string);
  bool parse_file();
  bool valid_;
  std::ifstream file_ = std::ifstream();;
  GeneralOptions general_options_;
  AudioSettings audio_settings_;
  MicrophoneInputSettings microphone_input_settings_;
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
  std::vector<int> microphone_input_device_ids_;
  std::vector<int> microphone_input_device_delays_;
};
}  // namespace utils
}  // namespace taylortrack

#endif  // TAYLORTRACK_UTILS_CONFIG_PARSER_H_
