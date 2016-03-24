/**
* @file
* @brief Implementation of a simple voice activity tracker
* @version 1
*/

#include <complex.h>
#include <valarray>
#include <vector>
#include "vad_simple.h"

namespace taylortrack {
  namespace utils {

    VadSimple::VadSimple(double threshold) {
      threshold_ = threshold;
    }

    bool VadSimple::detect(RArray &sample) {
      if(sample.size() > 0) {
        RArray result = std::pow(sample, 2.0);
        return threshold_ <= result.sum() / result.size();
      }
      return false;
    }

  }//namespace utils
}//namespace taylortrack