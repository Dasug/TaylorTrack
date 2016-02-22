/**
* @file
* @brief Implementation of the fft_strategy using the cooley turkey algorithm. This implementation however only works with
* signals that have a length equal to a power of two.
* @version 1
*/
#ifndef TAYLORTRACK_FFT_STRATEGY_H
#define TAYLORTRACK_FFT_STRATEGY_H

#include <vector>
#include <valarray>
#include <complex>

namespace taylortrack {
  namespace utils {
    typedef std::complex<double> Complex;
    typedef std::valarray<double> RArray;
    typedef std::valarray<Complex> CArray;
    /**
    * @interface fft_strategy
    * @brief Implementation of the fft_strategy using the cooley turkey algorithm. This implementation however only works with
    * signals that have a length equal to a power of two.
    *
    */
    class fft_strategy {
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
      virtual void fftshift(RArray &outvec, RArray &invec) = 0;


        /**
         * @brief Perform a circular shift on a given signal. The shifted signal will be placed in the parameter out.
         * @param outvec The valarray that has to contain the shifted signal.
         * @param invec The valarray that contains the signal that has to be shifted.
         * @param xdim The x dimension of the given vector.
         * @param ydim The y dimension of the given vector.
         * @param xshift The amount to shift in the x dimension.
         * @param yshift The amount to shift in the y dimension.
         */
      virtual void circshift(RArray &out, RArray &in, long xdim, long ydim, unsigned long xshift, unsigned long yshift);

      /**
      * @brief creates a complex val array out of a real one by filling imaginary parts with zeros.
      * @param x a valarray filled with complex values
      * return a valarray filled with complex numbers.
      */
      virtual CArray convertToComplex(RArray &signal);

      /**
      * @brief creates a real val array out of a complex one by cutting of all imaginary values.
      * @param x a valarray filled with complex values
      * return a valarray filled with doubles which represent the real parts of the input valarray
      */
      virtual RArray convertToReal(CArray &signal);

      /**
      * @brief Zero pad a signal with a variable amount.
      * @param signal a discrete audio signal
      * @param padamount amount of leading zeros
      * Creates a zero padded signal
      */
      virtual CArray zeroPadding(CArray &signal, int padamount);
    };
  } // namespace utils
} // namespace taylortrack

#endif //TAYLORTRACK_FFT_STRATEGY_H
