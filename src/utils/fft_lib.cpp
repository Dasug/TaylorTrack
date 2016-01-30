//
// Created by Jannis Hoppe on 28.01.16.
//
#include <iostream>
#include "fft_lib.h"
#include <valarray>
#include <complex>
const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray <Complex> CArray;
typedef std::valarray<double> RArray;


void taylortrack::utils::FftLib::fft(CArray &x) {

    const size_t N = x.size();
    if (N <= 1) return;

    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];

    // conquer
    fft(even);
    fft(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
            }


void taylortrack::utils::FftLib::ifft(CArray &x) {

                // conjugate the complex numbers
                x = x.apply(std::conj);

                // forward fft
                taylortrack::utils::FftLib::fft(x);

                // conjugate the complex numbers again
                x = x.apply(std::conj);

                // scale the numbers
                x /= x.size();
            }

            void taylortrack::utils::FftLib::circshift(RArray &out, RArray &in, int xdim, int ydim, int xshift, int yshift) {
                for (int i = 0; i < xdim; i++) {
                    int ii = (i + xshift) % xdim;
                    if (ii < 0) ii = xdim + ii;
                    for (int j = 0; j < ydim; j++) {
                        int jj = (j + yshift) % ydim;
                        if (jj < 0) jj = ydim + jj;
                        out[ii * ydim + jj] = in[i * ydim + j];
                    }
                }
            }


void taylortrack::utils::FftLib::fftshift(RArray &outvec, RArray &invec) {
    // xdim is 1 since we only deal with col vectors
    // xshift is 0 since we obviously never shift vectors along the x or row axis
    int yshift = floor(invec.size()/2);
    taylortrack::utils::FftLib::circshift(outvec,invec,1,invec.size(),0, yshift);

}

CArray taylortrack::utils::FftLib::zeropadding(CArray &signal, int padamount) {
    int newsize = padamount + signal.size();
    CArray paddedsignal(newsize);
    for(int i=0;i<padamount;i++){
        paddedsignal[i] = 0;
    }
    paddedsignal[std::slice(padamount,newsize,1)] = signal;
    return paddedsignal;
}
