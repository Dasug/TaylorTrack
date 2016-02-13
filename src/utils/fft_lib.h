//
// Created by Jannis Hoppe on 28.01.16.
//

#ifndef TAYLORTRACK_FFT_LIB_H
#define TAYLORTRACK_FFT_LIB_H

#include <valarray>
#include <complex>
#include "fft_strategy.h"

namespace taylortrack {
    namespace utils {
        class FftLib: public fft_strategy{
        public:
            typedef std::complex<double> Complex;
            typedef std::valarray<double> RArray;
            typedef std::valarray<Complex> CArray;



            /**
            * @brief Perform a fast fourier transformation on a signal
            * @param x Discrete audio signal.
            *
            *
            */
            void fft(CArray &x);
            /**
            * @brief Perform an inverse fast fourier transformation on a signal
            * @param x Discrete audio signal.
            *
            */
            void ifft(CArray& x);

            /**
            * @brief Performs a fftshift on a given valarray and writes the shifted vector into another given valarray.
            * @param outvec The valarray that has to contain the shifted valarray
            * @param invec The valarray that contains the original valarray
            */
            void fftshift(RArray &outvec, RArray &invec);

        };
    }
}

#endif //TAYLORTRACK_FFT_LIB_H
