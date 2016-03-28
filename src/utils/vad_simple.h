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
* @brief Simple Voice Activity Detection Implementation
* @version 1
*/

#ifndef TAYLORTRACK_UTILS_VAD_SIMPLE_H_
#define TAYLORTRACK_UTILS_VAD_SIMPLE_H_
#include "utils/vad_strategy.h"

namespace taylortrack {
namespace utils {
/**
* @class VadSimple
* @brief Implements a simple Voice Activity Detection
*/
class VadSimple : public VadStrategy {
 public:
  /**
   * @brief Constructor
   * @param threshold for audio signal to be classified as voice
   */
  explicit VadSimple(double threshold);

  /**
   * @brief energy based detection
   * @param &sample
   * @return true if voice is detected
   */
  bool detect(const RArray &sample) override;

  /**
   * @brief Getter Method for threshold
   * @return threshold value
   */
  double get_Threshold() const {
    return threshold_;
  }

  /**
   * @brief Setter Method for threshold
   * @param threshold wanted threshold
   */
  void set_Threshold(double threshold) {
    threshold_ = threshold;
  }

  VadSimple(const VadSimple& that) = default;
 private:
  double threshold_;  // significant value for classifying as voice
};
}  // namespace utils
}  // namespace taylortrack
#endif  // TAYLORTRACK_UTILS_VAD_SIMPLE_H_
