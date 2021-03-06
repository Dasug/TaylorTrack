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
*/
#ifndef TAYLORTRACK_UTILS_FFT_STRATEGY_H_
#define TAYLORTRACK_UTILS_FFT_STRATEGY_H_

#include <complex>
#include <valarray>
#include <vector>

namespace taylortrack {
namespace utils {
/**
 * @typedef ComplexDouble
 * Complex number type
 */
typedef std::complex<double> ComplexDouble;
/**
 * @typedef RArray
 * valarray filled with double values.
 */
typedef std::valarray<double> RArray;
/**
 * @typedef CArray
 * valarray filled with complex values.
 */
typedef std::valarray<ComplexDouble> CArray;
/**
* @class FftStrategy
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
  * @param invec The valarray that contains the signal that has to be shifted.
  * @param outvec The valarray that has to contain the shifted signal.
  */
  virtual void fftshift(const RArray &invec, RArray &outvec) = 0;


    /**
     * @brief Perform a circular shift on a given signal. The shifted signal will be placed in the parameter out.
     * @param in The valarray that contains the signal that has to be shifted.
     * @param xdim The x dimension of the given vector.
     * @param ydim The y dimension of the given vector.
     * @param xshift The amount to shift in the x dimension.
     * @param yshift The amount to shift in the y dimension.
     * @param out The valarray that has to contain the shifted signal.
     */
  virtual void circshift(const RArray &in,
                         int64_t xdim, int64_t ydim,
                         int64_t xshift, int64_t yshift, RArray &out);

  /**
  * @brief creates a complex val array out of a real one by filling imaginary parts with zeros.
  * @param signal a valarray filled with complex values
  * @return a valarray filled with complex numbers.
  */
  virtual CArray convert_to_complex(const RArray &signal);

  /**
  * @brief creates a real val array out of a complex one by cutting of all imaginary values.
  * @param signal a valarray filled with complex values
  * @return a valarray filled with doubles which represent the real parts of the input valarray
  */
  virtual RArray convert_to_real(const CArray &signal);

  /**
  * @brief Zero pad a signal with a variable amount.
  * @param signal a discrete audio signal
  * @param padamount amount of leading zeros
  * @return a zero padded signal
  */
  virtual CArray zero_padding(const CArray &signal, int padamount);
};
}  //  namespace utils
}  //  namespace taylortrack

#endif  // TAYLORTRACK_UTILS_FFT_STRATEGY_H_
