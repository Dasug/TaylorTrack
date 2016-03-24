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
* @brief Fast Fourier Transformation Strategy.
* @version 1
*/
#ifndef TAYLORTRACK_FFT_STRATEGY_H
#define TAYLORTRACK_FFT_STRATEGY_H

#include <complex>
#include <valarray>
#include <vector>

namespace taylortrack {
namespace utils {
typedef std::complex<double> ComplexDouble;
typedef std::valarray<double> RArray;
typedef std::valarray<ComplexDouble> CArray;
/**
* @interface FftStrategy
* @brief Interface for a Fast Fourier Transformation Strategy.
*
* Already provides some pre-made functions that may also be overwritten if needed
*/
class FftStrategy {
 public:
  /**
  * @brief Perform a fast fourier transformation on a signal inplace
  * @param x Discrete audio signal.
  */
  virtual void fft(CArray &x) = 0;

  /**
  * @brief Perform an inverse fast fourier transformation on a signal inplace
  * @param x A Discrete audio signal to which a fft has been applied.
  */
  virtual void ifft(CArray &x) = 0;

  /**
  * @brief Perform a fftshift on a given signal.
  * @param outvec The valarray that has to contain the shifted signal.
  * @param invec The valarray that contains the signal that has to be shifted.
  */
  virtual void fftshift(RArray &outvec, const RArray &invec) = 0;


    /**
     * @brief Perform a circular shift on a given signal. The shifted signal will be placed in the parameter out.
     * @param outvec The valarray that has to contain the shifted signal.
     * @param invec The valarray that contains the signal that has to be shifted.
     * @param xdim The x dimension of the given vector.
     * @param ydim The y dimension of the given vector.
     * @param xshift The amount to shift in the x dimension.
     * @param yshift The amount to shift in the y dimension.
     */
  virtual void circshift(RArray &out, const RArray &in,
                         int64_t xdim, int64_t ydim,
                         int64_t xshift, int64_t yshift);

  /**
  * @brief creates a complex val array out of a real one by filling imaginary parts with zeros.
  * @param x a valarray filled with complex values
  * @return a valarray filled with complex numbers.
  */
  virtual CArray convertToComplex(const RArray &signal);

  /**
  * @brief creates a real val array out of a complex one by cutting of all imaginary values.
  * @param x a valarray filled with complex values
  * @return a valarray filled with doubles which represent the real parts of the input valarray
  */
  virtual RArray convertToReal(const CArray &signal);

  /**
  * @brief Zero pad a signal with a variable amount.
  * @param signal a discrete audio signal
  * @param padamount amount of leading zeros
  * @return a zero padded signal
  */
  virtual CArray zeroPadding(const CArray &signal, int padamount);
};
}  //  namespace utils
}  //  namespace taylortrack

#endif  // TAYLORTRACK_FFT_STRATEGY_H
