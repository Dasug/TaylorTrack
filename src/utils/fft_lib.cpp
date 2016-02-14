#include "fft_lib.h"
#include <iostream>

const double kPI = 3.141592653589793238460;

namespace taylortrack {
  namespace utils {
    void FftLib::fft(CArray &x) {
      const size_t N = x.size();
      if (N <= 1) return;

      // divide
      CArray even = x[std::slice(0, N / 2, 2)];
      CArray odd = x[std::slice(1, N / 2, 2)];

      // conquer
      fft(even);
      fft(odd);

      // combine
      for (size_t k = 0; k < N / 2; ++k) {
        ComplexDouble t = std::polar(1.0, -2 * kPI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
      }
    }

    void FftLib::ifft(CArray &x) {
      // conjugate the complex numbers
      x = x.apply(std::conj);

      // forward fft
      fft(x);

      // conjugate the complex numbers again
      x = x.apply(std::conj);

      // scale the numbers
      x /= x.size();
    }

    void FftLib::fftshift(RArray &outvec, RArray &invec) {
      // xdim is 1 since we only deal with col vectors
      // xshift is 0 since we obviously never shift vectors along the x or row axis
      unsigned long yshift = (unsigned long) floor(invec.size() / 2);
      fft_strategy::circshift(outvec, invec, 1, invec.size(), 0, yshift);
    }
  } // namsespace utils
} // namespace taylortrack
