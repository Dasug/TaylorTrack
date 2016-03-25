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
* @brief Implementation of the FftStrategy using the cooley turkey algorithm.
*
* This implementation however only works with signals that have a length equal to a power of two.
* @version 1
*/

#ifndef TAYLORTRACK_UTILS_FFT_LIB_H_
#define TAYLORTRACK_UTILS_FFT_LIB_H_

#include "utils/fft_strategy.h"
#include <complex>
#include <valarray>

namespace taylortrack {
namespace utils {
/**
* @class FftLib
* @brief Implementation of the FftStrategy using the cooley turkey algorithm.
*
* This implementation however only works with signals that have a length equal to a power of two.
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
  void fftshift(RArray &outvec, const RArray &invec);
};
}  // namespace utils
}  // namespace taylortrack
#endif  // TAYLORTRACK_FFT_LIB_H_
