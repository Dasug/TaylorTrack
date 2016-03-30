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
 * @brief Implementation of vision_tracker.h
 */
#include "localization/vision_tracker.h"
#include <algorithm>
#include <iostream>

namespace taylortrack {
namespace localization {

double VisionTracker::get_position() {
  double angle_difference = faces_[0].x + faces_[0].width/2;
  angle_difference -= camera_center_;
  angle_difference *= angle_per_pixel_;
  angle_difference += 360 + camera_angle_;
  angle_difference = fmod(angle_difference, 360);

  return  angle_difference;
}

RArray VisionTracker::get_position_distribution() {
  RArray distribution(360);
  double mean = get_position();
  for (int i = 0; i < 360; ++i) {
    // Calculates the normal distribution from the position of the localized person.
    double dist_one = (1 / sqrt(2 * kPI * variance_)) *
        exp(-((i - mean) * (i - mean)) / (2 * variance_));
    double dist_two = (1 / sqrt(2 * kPI * variance_)) *
        exp(-((i - (mean + 360)) * (i - (mean + 360))) /
            (2 * variance_));
    double dist_three = (1 / sqrt(2 * kPI * variance_)) *
        exp(-((i - (mean - 360)) * (i - (mean - 360))) /
            (2 * variance_));
    distribution[i] = std::max({dist_one, dist_two, dist_three});
  }
  return distribution;
}

bool VisionTracker::set_parameters(const utils::VideoSettings &vs) {
  width_ = vs.width;
  camera_center_ = width_ / 2;
  max_camera_view_angle_ = vs.max_camera_view_angle;
  angle_per_pixel_ = max_camera_view_angle_ / width_;
  variance_ = vs.variance;
  camera_angle_ = vs.camera_angle;
  std::cout << max_camera_view_angle_ << std::endl;
  initialised_ = face_cascade_.load(vs.face_cascade_name);
  return initialised_;
}

void VisionTracker::set_frame(cv::Mat frame) {
  frame_ = frame;
}

bool VisionTracker::detect_person() {
  face_cascade_.detectMultiScale(frame_, faces_, 1.1, 2,
                                 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
  return !faces_.empty();
}

bool VisionTracker::is_initialised() {
  return initialised_;
}
std::vector<cv::Rect> VisionTracker::get_faces() {
  return faces_;
}

}  // namespace localization
}  // namespace taylortrack
