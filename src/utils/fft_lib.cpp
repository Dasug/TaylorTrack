#include "fft_lib.h"
#include <iostream>

const double kPI = 3.141592653589793238460;

namespace taylortrack {
  namespace utils {
    void FftLib::fft(CArray &signal) {
      const size_t N = signal.size();
      if (N <= 1) return;

      // divide: Splitting in even and odd part of the signal
      CArray even = signal[std::slice(0, N / 2, 2)];
      CArray odd = signal[std::slice(1, N / 2, 2)];

      // conquer: Recursive call with the previously splitted signal.
      fft(even);
      fft(odd);

      // combine
      for (size_t k = 0; k < N / 2; ++k) {
        ComplexDouble t = std::polar(1.0, -2 * kPI * k / N) * odd[k];
        signal[k] = even[k] + t;
        signal[k + N / 2] = even[k] - t;
      }
    }

    void FftLib::ifft(CArray &signal) {
      // conjugate the complex numbers
      signal = signal.apply(std::conj);

      // forward fft
      fft(signal);

      // conjugate the complex numbers again
      signal = signal.apply(std::conj);

      // scale the numbers
      signal /= signal.size();
    }

    void FftLib::fftshift(RArray &outvec, RArray &invec) {
      // xdim is 1 since we only deal with col vectors
      // xshift is 0 since we obviously never shift vectors along the x or row axis
      unsigned long yshift = (unsigned long) floor(invec.size() / 2);
      FftStrategy::circshift(outvec, invec, 1, invec.size(), 0, yshift);
    }
  } // namsespace utils
} // namespace taylortrack
