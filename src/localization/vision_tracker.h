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
* @brief Implements the person tracking by using OpenCV
* @version 1
*/
#ifndef TAYLORTRACK_LOCALIZATION_VISION_TRACKER_H
#define TAYLORTRACK_LOCALIZATION_VISION_TRACKER_H
#include <vector>
#include "localization/video_localizer.h"

namespace taylortrack {
namespace localization {
/**
* @class VisionTracker
* @brief Implements the VideoLocalizer interface.
*
* Strategy that utilizes OpenCV to localize a person in front of the camera.
*/
class VisionTracker : public VideoLocalizer {
 public:
  /**
  * @brief Gets most likely position of the located person in degrees
  * @return Position of the person in degree
  */
  double get_position();
  /**
  * @brief Returns a probability distribution for the position of the person over all degrees
  * @return A RArray with all probability values
  */
  RArray get_position_distribution();
  /**
  * @brief Sets all relevant parameters of the person tracking algorithm.
  * @param  Settings a struct of type VideoSettings
  * @return True if the video settings have been set and if the CascadeCassifier was loaded correctly.
  */
  bool set_parameters(const utils::VideoSettings &vs);
  /**
  * @brief Sets the frame for the person detection.
  * @param  A OpenCV Matrix containing the frame to be used for the detection.
  */
  void set_frame(cv::Mat frame);
  /**
  * @brief Checks if a person is in the frame and stores his position.
  * @return True if a person is detected, otherwise returns false.
  */
  bool detect_person();
  /**
  * @brief Checks if this class has been initialised.
  * @return True if a person the set_parameters function was successfully called, otherwise returns false.
  */
  bool is_initialised();

 private:
  bool initialised_ = false;
  cv::CascadeClassifier face_cascade_;
  cv::Mat frame_;
  std::vector<cv::Rect> faces_;
  int width_ = 0, camera_center_ = 0;
  double angle_per_pixel_ = 0, variance_ = 0,
      max_camera_view_angle_ = 0, camera_angle_ = 0;
};
}  // namespace localization
}  // namespace taylortrack
#endif  // TAYLORTRACK_VISION_TRACKER_H
