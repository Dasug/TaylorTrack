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
* @brief Header file for the structs for the algorithm configuration.
* @version 1
*/
#ifndef TAYLORTRACK_UTILS_CONFIG_H_
#define TAYLORTRACK_UTILS_CONFIG_H_
#include <valarray>
#include <string>

namespace taylortrack {
namespace utils {
/**
 * @Struct
 * @brief Contains general options.
 */
struct GeneralOptions {
  /**
   * @var console_output
   * Defines whether the user wants to have a console output for the results of the algorithm.
  */
  bool console_output = true;
};

/**
* @Struct
* @brief Contains the parameters for the audio tracking algorithm.
*/
struct AudioSettings {
  /**
   * @var outport
   * Defines the yarp output port for the speaker tracking algorithm.
   * @deprecated Use CommunicationSettings struct instead
  */
  std::string outport = "/bp39_audio_out";

  /**
   * @var inport
   * Defines the yarp input port for the speaker tracking algorithm.
   * @deprecated Use CommunicationSettings struct instead
  */
  std::string inport  = "/bp39_audio_in";

  /**
   * @var sample_rate
   * Defines the sample rate for the speaker tracking algorithm.
  */
  int sample_rate = 44100;

  /**
   * @var mic_x
   * Defines a valarray of doubles which stores the x coordinate for each microphone.
  */
  std::valarray<double> mic_x;

  /**
   * @var mic_y
   * Defines a valarray of doubles which stores the y coordinate for each microphone.
  */
  std::valarray<double> mic_y;

  /**
   * @var beta
   * Defines the beta value for the speaker tracking algorithm.
  */
  double beta = 0.7;

  /**
   * @var grid_x
   * Defines the number of values on the x axis.
  */
  double grid_x = 4;

  /**
   * @var grid_y
   * Defines the number of values on the y axis.
  */
  double grid_y = 4;

  /**
   * @var interval
   * Defines the interval/step size of the axis.
  */
  double interval = 0.1;

  /**
   * @var frame_size
   * Defines the frame size for the speaker tracking algorithm.
  */
  int frame_size = 2048;
};

/**
* @Struct
* @brief Contains the parameters for the vision tracking algorithm.
*/
struct VideoSettings {
  /**
   * @var outport
   * Defines the yarp output port for the vision tracking algorithm.
   * @deprecated Use CommunicationSettings struct instead
  */
  std::string outport = "/bp39_video_out";
  /**
   * @var inport
   * Defines the yarp input port for the vision tracking algorithm.
   * @deprecated Use CommunicationSettings struct instead
  */
  std::string inport  = "/bp39_video_in";

  /**
   * @var face_cascade_name
   * Defines the opencv cascade for face detection.
   */
  std::string face_cascade_name = "haarcascade_frontalface_alt.xml";

  /**
   * @var frame_skip
   * Defines the number of frames that should be skipped.
   */
  int frame_skip = 0;

  /**
   * @var camera_id
   * Defines the id of the camera which should be used.
   */
  int camera_id = -1;
};

/**
 * @Struct
 * @brief Contains configuration for Audio and Video Combination tracking
 */
struct CombinationSettings {
  /**
   * @var outport
   * Defines the yarp input port for the vision tracking algorithm.
   * @deprecated Use CommunicationSettings struct instead
  */
  std::string outport = "/bp39_combination_out";
  /**
   * @var inport
   * Defines the yarp input port for the vision tracking algorithm.
   * @deprecated Use CommunicationSettings struct instead
  */
  std::string inport  = "/bp39_combination_in";
};

/**
 * @Struct
 * @brief Contains parameters for network communication.
 */
struct CommunicationSettings {
  /**
   * @var port
   * Defines the yarp port used for input or output.
  */
  std::string port = "/unnamed_port";
};
}  // namespace utils
}  // namespace taylortrack
#endif  // TAYLORTRACK_CONFIG_H
