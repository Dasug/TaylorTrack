/**
* @file
* @brief Implementation of A Voice Activity Strategy
* @version 1
*/
#ifndef TAYLORTRACK_VADSTRATEGY_H_
#define TAYLORTRACK_VADSTRATEGY_H_

#include <complex.h>
#include <vector>
#include <valarray>

namespace taylortrack {
  namespace utils {
  typedef std::complex<double> ComplexDouble;
  typedef std::valarray<double> RArray;
  typedef std::valarray<ComplexDouble> CArray;
    /**
    * @class VadStrategy
    * @brief Interface for Voice Activity Trackers with parsed samples
    */
    class VadStrategy {
     public:
      /**
       * @brief tracks voice activity for a given sample
       * @param &sample
       * @return true if voice activity has been tracked in given sample
       */
      virtual bool detect(RArray &sample) = 0;
    };
  }//namespace utils
}//namespace taylortrack

#endif //TAYLORTRACK_VADSTRATEGY_H
