/**
* @file
* @brief Header file for the structs for the algorithm configuration.
* @version 1
*/
#ifndef TAYLORTRACK_CONFIG_H_
#define TAYLORTRACK_CONFIG_H_
#include <valarray>
#include <string>
#include <vector>

namespace taylortrack {
namespace utils {
/**
 * @Struct
 * @brief Contains settings for a single microphone device.
 */
struct MicrophoneDevice {
  /**
   * @var name
   * id of the device (starting the Taylortrack Microphone Input program will show a list of all available sound devices).
  */
  int microphone_id = 0;

  /**
   * @var delay
   * number of samples that input device should be delayed when combining audio streams of several input devices
  */
  int delay = 0;

  /**
   * @var channels
   * number of channels within the input device
   */
  int channels = 0;
};

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
 * @brief Contains the parameters for the microphone input.
 */
struct MicrophoneInputSettings {
  /**
   * @var devices
   * A std::vector including settings for all microphone devices to be used
   */
  std::vector<MicrophoneDevice> devices = {};

  /**
   * @var sample_rate
   * Defines the sample rate for the microphone input.
  */
  int sample_rate = 44100;

  /**
   * @var frame_size
   * Defines the amount of samples per channel that are being recorded per frame.
  */
  int frame_size = 2048;
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
  double frame_size = 2048;
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
} // utils
} // taylortrack
#endif //TAYLORTRACK_CONFIG_H
