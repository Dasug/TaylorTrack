//
// Created by Jannis Hoppe on 28.01.16.
//

#ifndef TAYLORTRACK_FFT_LIB_H
#define TAYLORTRACK_FFT_LIB_H
#include <valarray>
#include <complex>

namespace taylortrack {
    namespace utils {
        class FftLib {
        public:

            typedef std::complex<double> Complex;
            typedef std::valarray <Complex> CArray;
            typedef std::valarray<double> RArray;
            /**
            * @brief Zero pad a signal with a variable amount.
            * @param signal a discrete audio signal
            * @param padamount amount of leading zeros
            * Creates a zero padded signal
            *
            */
            static CArray zeropadding(CArray &signal,int padamount);
            /**
            * @brief Perform a fast fourier transformation on a signal
            * @param x Discrete audio signal.
            *
            *
            */
            static void fft(CArray &x);
            /**
            * @brief Perform an inverse fast fourier transformation on a signal
            * @param x Discrete audio signal.
            *
            */
            static void ifft(CArray& x);

            static void fftshift(RArray &outvec, RArray &invec);

            static void circshift(RArray &out, RArray &in, int xdim, int ydim, int xshift, int yshift);


            static CArray converttocomp(RArray &x);
            static RArray converttoreal(CArray &x);
        };
    }
}

#endif //TAYLORTRACK_FFT_LIB_H
