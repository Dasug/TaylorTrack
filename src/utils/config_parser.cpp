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
* @brief Implementation of the config_parser.h
*/
#include "utils/config_parser.h"
#include <iomanip>
#include <string>
#include <vector>

namespace taylortrack {
namespace utils {
ConfigParser::ConfigParser(const char *file_name) {
  file_ = std::move(std::ifstream(file_name, std::ios::in|std::ios::binary));

  if (file_) {
    valid_ = parse_file();
  } else {
    std::cout << "Error could not parse file." << std::endl;
    valid_ = false;
    file_.close();
  }
}

bool ConfigParser::parse_file() {
  if (!file_)
    return false;

  // 0 = options, 1 = audio, 2 = video,
  // 3 = combination, 4 = input, 5 = visualizer
  // 6 = microphone input, 7 = wave input
  int section = -1;
  std::string line = "";
  while (std::getline(file_, line)) {
    std::vector<std::string> split_string = split(line, '=');

    if (split_string.size() < 2 && line.find('[') == std::string::npos)
      continue;

    if (split_string.size() > 2 ||
        (split_string.size() == 2 &&
            trim(split_string[1]).empty()))
      return false;

    if (!line.empty() && line.at(0) != '[' && line.at(0)
        != '#' && !isspace(line.at(0))) {
      split_string[0] = trim(split_string[0]);
      split_string[1] = trim(split_string[1]);
      switch (section) {
        case 0:  // [options]
          if (split_string[0].compare("console_output") == 0)
            general_options_.console_output =
                split_string[1].compare("true") == 0;
          break;  // end section 0

        case 1:  // [audio]
          if (split_string[0].compare("inport") == 0) {
            audio_settings_.inport = split_string[1];
            audio_communication_in_.port = split_string[1];
          } else if (split_string[0].compare("outport") == 0) {
            audio_settings_.outport = split_string[1];
            audio_communication_out_.port = split_string[1];
          } else if (split_string[0].compare("destination") == 0) {
            audio_communication_destination.port = split_string[1];
          } else if (split_string[0].compare("sample_rate") == 0) {
            std::istringstream(split_string[1]) >>
                audio_settings_.sample_rate;
          } else if (split_string[0].compare("mic_x") == 0) {
            std::vector<std::string> mic = split_microphones(split_string[1]);
            audio_settings_.mic_x.resize(mic.size());
            for (int i = 0; i < static_cast<int>(mic.size()); i++)
              std::stringstream(mic[i]) >> audio_settings_.mic_x[i];
          } else if (split_string[0].compare("mic_y") == 0) {
            std::vector<std::string> mic = split_microphones(split_string[1]);
            audio_settings_.mic_y.resize(mic.size());
            for (int i = 0; i < static_cast<int>(mic.size()); i++)
              std::stringstream(mic[i]) >>
                  audio_settings_.mic_y[i];
          } else if (split_string[0].compare("beta") == 0) {
            std::stringstream(split_string[1]) >>
                audio_settings_.beta;
          } else if (split_string[0].compare("grid_x") == 0) {
            std::stringstream(split_string[1]) >>
                audio_settings_.grid_x;
          } else if (split_string[0].compare("grid_y") == 0) {
            std::stringstream(split_string[1]) >>
                audio_settings_.grid_y;
          } else if (split_string[0].compare("interval") == 0) {
            std::stringstream(split_string[1]) >>
                audio_settings_.interval;
          } else if (split_string[0].compare("frame_size") == 0) {
            std::stringstream(split_string[1]) >>
                audio_settings_.frame_size;
          }
          break;  // end section 1

        case 2:  // [video]
          if (split_string[0].compare("inport") == 0) {
            video_settings_.inport = split_string[1];
            video_communication_in_.port = split_string[1];
          } else if (split_string[0].compare("outport") == 0) {
            video_settings_.outport = split_string[1];
            video_communication_out_.port = split_string[1];
          } else if (split_string[0].compare("destination") == 0) {
            video_communication_destination.port = split_string[1];
          } else if (split_string[0].compare("source") == 0) {
            video_communication_source.port = split_string[1];
          } else if (
              split_string[0].compare("face_cascade_name") == 0) {
            video_settings_.face_cascade_name = split_string[1];
          } else if (split_string[0].compare("camera_id") == 0) {
            std::stringstream(split_string[1]) >>
                video_settings_.camera_id;
          } else if (split_string[0].compare("width") == 0) {
            std::stringstream(split_string[1]) >>
                video_settings_.width;
          } else if (split_string[0].compare("max_camera_view_angle") == 0) {
            std::stringstream(split_string[1]) >>
                video_settings_.max_camera_view_angle;
          } else if (split_string[0].compare("camera_angle") == 0) {
            std::stringstream(split_string[1]) >>
                video_settings_.camera_angle;
          } else if (split_string[0].compare("variance") == 0) {
            std::stringstream(split_string[1]) >>
                video_settings_.variance;
          }
          break;  // end section 2

        case 3:  // [combination]
          if (split_string[0].compare("audio_inport") == 0) {
            combination_settings_.inport = split_string[1];
            combination_audio_communication_in_.port = split_string[1];
            combination_inports_.push_back(combination_audio_communication_in_);
          } else if (split_string[0].compare("video_inport") == 0) {
            combination_settings_.inport = split_string[1];
            combination_video_communication_in_.port = split_string[1];
            combination_inports_.push_back(combination_video_communication_in_);
          } else if (split_string[0].compare("weight") == 0) {
            std::vector<std::string> weights =
                split_microphones(split_string[1]);
            combination_settings_.weight.resize(weights.size());
            for (int i = 0; i < static_cast<int>(weights.size()); i++)
              std::stringstream(weights[i]) >>
                  combination_settings_.weight[i];
          } else if (split_string[0].compare("destination") == 0) {
            audio_settings_.outport = split_string[1];
            combination_communication_destination.port = split_string[1];
          } else if (split_string[0].compare("outport") == 0) {
            combination_settings_.outport = split_string[1];
            combination_communication_out_.port = split_string[1];
          }

          break;  // end section 3

        case 4:
          if (split_string[0].compare("outport") == 0)
            input_communication_out_.port = split_string[1];
          break;  // end section 4

        case 5:
          if (split_string[0].compare("inport") == 0)
            visualizer_communication_in_.port = split_string[1];
          break;  // end section 5

        case 6:
          if (split_string[0].compare("devices") == 0) {
            std::vector<std::string> mic = split_microphones(split_string[1]);
            for (uint i = 0; i < mic.size(); i++) {
              int microphone_id = 0;
              std::stringstream(mic[i]) >> microphone_id;
              microphone_input_device_ids_.push_back(microphone_id);
            }
          } else if (split_string[0].compare("delays") == 0) {
            std::vector<std::string> microphones =
                split_microphones(split_string[1]);
            for (uint i = 0; i < microphones.size(); i++) {
              int microphone_delay = 0;
              std::stringstream(microphones[i]) >> microphone_delay;
              microphone_input_device_delays_.push_back(microphone_delay);
            }
          } else if (split_string[0].compare("frame_size") == 0) {
            std::stringstream(split_string[1]) >>
                microphone_input_settings_.frame_size;
          }
          break;  // end section 6

        case 7:
          if (split_string[0].compare("frame_size") == 0)
            std::stringstream(split_string[1]) >>
                wave_input_settings_.frame_size;
          break;  // end section 7

        default:  // Do nothing
          break;
      }
    }
    if (line.compare("[options]") == 0)
      section = 0;
    else if (line.compare("[audio]") == 0)
      section = 1;
    else if (line.compare("[video]") == 0)
      section = 2;
    else if (line.compare("[combination]") == 0)
      section = 3;
    else if (line.compare("[input]") == 0)
      section = 4;
    else if (line.compare("[visualizer]") == 0)
      section = 5;
    else if (line.compare("[microphone input]") == 0)
      section = 6;
    else if (line.compare("[wave input]") == 0)
      section = 7;
  }  // end while

  // create proper microphone device objects
  for (int device_index = 0;
       device_index < static_cast<int>(microphone_input_device_ids_.size());
       ++device_index) {
    MicrophoneDevice device;
    device.microphone_id = microphone_input_device_ids_.at(
        static_cast<u_int64_t>(device_index));
    if (static_cast<int>(
        microphone_input_device_delays_.size()) > device_index) {
      device.delay = microphone_input_device_delays_.at(
          static_cast<u_int64_t>(device_index));
    } else {
      device.delay = 0;
    }

    microphone_input_settings_.devices.push_back(device);
  }

  return audio_settings_.mic_x.size() == audio_settings_.mic_y.size()
      && audio_settings_.mic_x.size() > 0
      && audio_settings_.mic_y.size() > 0;
}

// Method to split a string by the given delim.
std::vector<std::string>
ConfigParser::split(const std::string &temporary_string,
                    char delimiter) {
  std::vector<std::string> elements;
  std::stringstream stringstream(temporary_string);
  std::string item = "";

  while (std::getline(stringstream, item, delimiter))
    elements.push_back(item);

  return elements;
}

std::vector<std::string>
ConfigParser::split_microphones(std::string temporary_string) {
  std::vector<std::string> elements;
  int start = -1;

  for (int i = 0; i < static_cast<int>(temporary_string.length()); ++i) {
    if (std::isspace(temporary_string[i]) == 0 && start == -1) {
      if (i == static_cast<int>(temporary_string.length()) - 1)
        elements.push_back(
            temporary_string.substr(static_cast<u_int64_t>(i)));
      start = i;
    } else if ((std::isspace(temporary_string[i]) != 0
        && start != -1)
        || i == static_cast<int>(temporary_string.length()) - 1) {
      if (i == static_cast<int>(temporary_string.length() -1))
        elements.push_back(
            temporary_string.substr(
                static_cast<unsigned int>(start),
                static_cast<u_int64_t>(i + 1 - start)));
      else
        elements.push_back(
            temporary_string.substr(
                static_cast<unsigned int>(start),
                static_cast<u_int64_t>(i - start)));
      start = -1;
    }
  }
  return elements;
}

// Method to remove whitespaces,
// tabulator etc. from the the front and back of the string.
std::string ConfigParser::trim(const std::string &temporary_string) {
  auto whitespace_front =
      std::find_if_not(temporary_string.begin(),
                       temporary_string.end(),
                       [](int c){return std::isspace(c);});
  auto whitespace_back =
      std::find_if_not(temporary_string.rbegin(),
                       temporary_string.rend(),
                       [](int c){return std::isspace(c);}).base();

  return whitespace_back <= whitespace_front ?
         std::string() :
         std::string(whitespace_front, whitespace_back);
}

ConfigParser::ConfigParser() {
  valid_ = true;
}

}  // namespace utils
}  // namespace taylortrack

