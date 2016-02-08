
#ifndef TAYLORTRACK_CONFIG_H
#define TAYLORTRACK_CONFIG_H
#include <valarray>

namespace taylortrack {
  namespace utils {
    struct Options {
      bool console_output = true;
    };

    struct Audio {
      std::string outport = "/bp39_audio_out";
      std::string inport  = "/bp39_audio_in";
      int sample_rate = 44100;
      std::valarray<double> mic_x;
      std::valarray<double> mic_y;
      double beta       = 0.7;
      double grid_x     = 4;
      double grid_y     = 4;
      double interval   = 0.1;
      double frame_size = 2048;
    };

    struct Video {
      std::string outport = "/bp39_video_out";
      std::string inport  = "/bp39_video_in";
    };

    struct Combination {
      std::string outport = "/bp39_combination_out";
      std::string inport  = "/bp39_combination_in";
    };
  } // utils
} // taylortrack
#endif //TAYLORTRACK_CONFIG_H
