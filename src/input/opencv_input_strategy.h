
#ifndef TAYLORTRACK_OPENCV_INPUT_STRATEGY_H
#define TAYLORTRACK_OPENCV_INPUT_STRATEGY_H

#include "input_strategy.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <yarp/sig/Matrix.h>
#include <stdint.h>
#include "../utils/config.h"

namespace taylortrack {
  namespace input {
    class OpenCVInputStrategy : public InputStrategy {
     public:
      yarp::os::Bottle read(yarp::os::Bottle &bottle);
      bool is_done();
      void set_parameters(taylortrack::utils::Parameters &params);
      void set_config(taylortrack::utils::ConfigParser &config_parser);
     private:
      cv::VideoCapture video_capture_;
      cv::Mat frame_;
      int frame_counter_ = 0, frame_skip_, camera_id_;
      bool done_ = false;
      cv::String window_name_ = "Capture - Face detection";


    };
  } //namespace input
} // namespace taylortrack

#endif //TAYLORTRACK_OPENCV_INPUT_STRATEGY_H
