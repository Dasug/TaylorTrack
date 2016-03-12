/**
* @file
* @brief Implementation of the fft_strategy using the cooley turkey algorithm. This implementation however only works with
* signals that have a length equal to a power of two.
* @version 1
*/

#ifndef TAYLORTRACK_FFT_LIB_H
#define TAYLORTRACK_FFT_LIB_H

#include "fft_strategy.h"
#include <valarray>
#include <complex>

namespace taylortrack {
  namespace utils {
    /**
    * @class fft_strategy
    * @brief Implementation of the fft_strategy using the cooley turkey algorithm. This implementation however only works with
    * signals that have a length equal to a power of two.
    *
    *
    */
    class FftLib: public FftStrategy {
     public:
      typedef std::complex<double> ComplexDouble;
      typedef std::valarray<double> RArray;
      typedef std::valarray<ComplexDouble> CArray;

      /**
      * @brief Perform a fast fourier transformation on a signal in place.
      * @param x Discrete audio signal.
      */
      void fft(CArray &x);
      /**
      * @brief Perform an inverse fast fourier transformation on a signal in place.
      * @param x Discrete audio signal.
      */
      void ifft(CArray &x);

      /**
      * @brief Performs a fftshift on a given valarray and writes the shifted vector into another given valarray.
      * @param outvec The valarray that has to contain the shifted valarray
      * @param invec The valarray that contains the original valarray
      */
      void fftshift(RArray &outvec, RArray &invec);
    };
  } //namespace utils
} // namespace taylortrack
#endif //TAYLORTRACK_FFT_LIB_H
