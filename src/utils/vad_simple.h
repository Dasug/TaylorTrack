/**
* @file
* @brief Simple Voice Activity Detection Implementation
* @version 1
*/

#ifndef TAYLORTRACK_VAD_SIMPLE_H_
#define TAYLORTRACK_VAD_SIMPLE_H_
#include "vad_strategy.h"

namespace taylortrack {
namespace utils {
/**
* @class VadSimple
* @brief Implements a simple Voice Activity Detection
*/
class VadSimple: public VadStrategy {
 public:
  /**
   * @brief Constructor
   * @param threshold for audio signal to be classified as voice
   */
  VadSimple(double threshold);

  /**
   * @brief energy based detection
   * @param &sample
   * @return true if voice is detected
   */
  bool detect(RArray &sample);

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

 private:
  double threshold_; //significant value for classifying as voice
};
} // namespace input
} // namespace taylortrack
#endif // TAYLORTRACK_VAD_SIMPLE_H_