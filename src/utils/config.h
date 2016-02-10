/**
* @file
* @brief Header file for the structs for the algorithm configuration.
* @version 1
*/
#ifndef TAYLORTRACK_CONFIG_H
#define TAYLORTRACK_CONFIG_H
#include <valarray>

namespace taylortrack {
  namespace utils {
    /**
     * @Struct
     * @brief Contains general options.
     */
    struct Options {
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
    struct Audio {
      /**
       * @var outport
       * Defines the yarp output port for the speaker tracking algorithm.
      */
      std::string outport = "/bp39_audio_out";

      /**
       * @var inport
       * Defines the yarp input port for the speaker tracking algorithm.
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
    struct Video {
      /**
       * @var outport
       * Defines the yarp output port for the vision tracking algorithm.
      */
      std::string outport = "/bp39_video_out";
      /**
       * @var inport
       * Defines the yarp input port for the vision tracking algorithm.
      */
      std::string inport  = "/bp39_video_in";
    };

    struct Combination {
      /**
       * @var outport
       * Defines the yarp input port for the vision tracking algorithm.
      */
      std::string outport = "/bp39_combination_out";

      /**
       * @var inport
       * Defines the yarp input port for the vision tracking algorithm.
      */
      std::string inport  = "/bp39_combination_in";
    };
  } // utils
} // taylortrack
#endif //TAYLORTRACK_CONFIG_H
