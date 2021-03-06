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
* @brief Fast Fourier Transformation Implementation.
*/
#include "utils/fft_lib.h"
#include <iostream>

namespace taylortrack {
namespace utils {
void FftLib::fft(CArray &signal) {
  const size_t signal_size = signal.size();
  if (signal_size <= 1) return;

  // divide: Splitting in even and odd part of the signal
  CArray even = signal[std::slice(0, signal_size / 2, 2)];
  CArray odd = signal[std::slice(1, signal_size / 2, 2)];

  // conquer: Recursive call with the previously splitted signal.
  fft(even);
  fft(odd);

  // combine
  for (size_t k = 0; k < signal_size / 2; ++k) {
    ComplexDouble t = std::polar(1.0, -2 * kPI * k / signal_size) * odd[k];
    signal[k] = even[k] + t;
    signal[k + signal_size / 2] = even[k] - t;
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

void FftLib::fftshift(const RArray &invector, RArray &outvector) {
  // xdim is 1 since we only deal with col vectors.
  // xshift is 0 since we obviously never shift
  // vectors along the x or row axis.
  int64_t yshift = int64_t(floor(invector.size() / 2));
  FftStrategy::circshift(invector, 1, invector.size(), 0, yshift, outvector);
}
}  // namespace utils
}  // namespace taylortrack
