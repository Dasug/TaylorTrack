/**
* @file
* @brief Header file for the structs for the algorithm configuration.
* @version 1
*/
#ifndef TAYLORTRACK_CONFIG_H
#define TAYLORTRACK_CONFIG_H
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
      std::string face_cascade_name = "";

      /**
       * @var camera_id
       * Defines the id of the camera which should be used.
       */
      int camera_id = 0;

      int width = 0;

      double max_camera_view_angle = 0;

      double camera_angle = 0;

      double variance = 0;
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
