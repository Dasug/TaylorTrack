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

#ifndef TAYLORTRACK_SRC_INPUT_OPENCV_INPUT_STRATEGY_H_
#define TAYLORTRACK_SRC_INPUT_OPENCV_INPUT_STRATEGY_H_

#include "input_strategy.h"
#ifdef OLD_OPENCV_HEADERS
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#else
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#endif
#include <stdint.h>
#include <yarp/sig/Matrix.h>
#include "utils/config.h"

namespace taylortrack {
namespace input {
class OpenCVInputStrategy : public InputStrategy {
 public:
  OpenCVInputStrategy() = default;
  /**
   * @brief Default Copy constructor
   */
  OpenCVInputStrategy(const OpenCVInputStrategy &that) = default;
  yarp::os::Bottle read(yarp::os::Bottle *bottle) override;
  bool is_done() override;
  void set_parameters(const taylortrack::utils::Parameters &params) override;
  void set_config(const taylortrack::utils::ConfigParser &config_parser) override;
 private:
  cv::VideoCapture video_capture_;
  cv::Mat frame_;
  int frame_counter_ = 0, frame_skip_, camera_id_;
  bool done_ = false;
  cv::String window_name_ = "Capture - Face detection";
};
}  // namespace input
}  // namespace taylortrack
#endif  // TAYLORTRACK_SRC_INPUT_OPENCV_INPUT_STRATEGY_H_
