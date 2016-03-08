
#include "fft_strategy.h"

namespace taylortrack {
  namespace utils {
    void fft_strategy::circshift(RArray &out,
                                 RArray &in,
                                 long xdim,
                                 long ydim,
                                 unsigned long xshift,
                                 unsigned long yshift) {
      for (long i = 0; i < xdim; i++) {
        long ii = (i + xshift) % xdim;
        for (long j = 0; j < ydim; j++) {
          long jj = (j + yshift) % ydim;
          out[ii * ydim + jj] = in[i * ydim + j];
        }
      }
    }

    CArray fft_strategy::convertToComplex(RArray &signal) {
      CArray converted(signal.size());
      for (int i = 0; i < signal.size(); i++) {
        converted[i] = signal[i];
      }
      return converted;
    }

    RArray fft_strategy::convertToReal(CArray &signal) {
      RArray converted(signal.size());
      for (int i = 0; i < signal.size(); i++) {
        converted[i] = signal[i].real();
      }
      return converted;
    }

    CArray fft_strategy::zeroPadding(CArray &signal, int padamount) {
      size_t newsize = padamount + signal.size();
      CArray paddedsignal(newsize);
      // copying the signal
      for (size_t i = 0; i < signal.size(); i++) {
        paddedsignal[i] = signal[i];
      }
      // padding the original signal with the specified amount of zeros.
      for (size_t i = signal.size(); i < newsize; i++) {
        paddedsignal[i] = 0;
      }
      return paddedsignal;
    }
  } // namespace utils
} // namespace taylortrack

