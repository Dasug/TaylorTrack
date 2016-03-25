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

#ifndef TAYLORTRACK_LOCALIZATION_VIDEO_LOCALIZER_H_
#define TAYLORTRACK_LOCALIZATION_VIDEO_LOCALIZER_H_

#ifdef OLD_OPENCV_HEADERS
#include "opencv2/objdetect/objdetect.hpp"
#else
#include "opencv2/objdetect.hpp"
#endif
#include <vector>
#include <valarray>
#include "../utils/config.h"

namespace taylortrack {
namespace localization {
typedef std::valarray<double> RArray;
/**
* @interface Video Localizer
* @brief Interface for different video localization algorithms.
*
* Localization algorithm that will get used
*/
class VideoLocalizer {
 public:
  /**
  * @brief return suspected position of the person in degrees.
  * @return angle position of the person in the video frame.
  */
  virtual double get_position() = 0;
  /**
  * @brief Returns a probability distribution for the position of the person over all degrees
  * @return A RArray with all probability values
  */
  virtual RArray get_position_distribution() = 0;
  /**
  * @brief Sets all relevant parameters of the implemented algorithm. Missing Parameters have to be placed inside
  *        the VideoSettings struct.
  * @param taylortrack::utils::VideoSettings struct for the algorithm to take its configuration.
  * @pre taylortrack::utils::ConfigParser::is_valid() should return true
  */
  virtual bool set_parameters(const utils::VideoSettings &vs) = 0;
  /**
  * @brief Sets the frame for the person detection.
  * @param  A OpenCV Matrix containing the frame to be used for the detection.
  */
  virtual void set_frame(cv::Mat frame) = 0;
};
}  // namespace localization
}  // namespace taylortrack
#endif  // TAYLORTRACK_LOCALIZATION_VIDEO_LOCALIZER_H_
