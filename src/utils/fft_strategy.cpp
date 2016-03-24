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
#include "utils/fft_strategy.h"

namespace taylortrack {
namespace utils {
void FftStrategy::circshift(RArray &out,
                            const RArray &in,
                            int64_t xdim,
                            int64_t ydim,
                            int64_t xshift,
                            int64_t yshift) {
  for (int64_t i = 0; i < xdim; i++) {
    int64_t ii = (i + xshift) % xdim;
    for (int64_t j = 0; j < ydim; j++) {
      int64_t jj = (j + yshift) % ydim;
      out[ii * ydim + jj] = in[i * ydim + j];
    }
  }
}

CArray FftStrategy::convertToComplex(const RArray &signal) {
  CArray converted(signal.size());
  for (int i = 0; i < signal.size(); i++) {
    converted[i] = signal[i];
  }
  return converted;
}

RArray FftStrategy::convertToReal(const CArray &signal) {
  RArray converted(signal.size());
  for (int i = 0; i < signal.size(); i++) {
    converted[i] = signal[i].real();
  }
  return converted;
}

CArray FftStrategy::zeroPadding(const CArray &signal, int padamount) {
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
}  // namespace utils
}  // namespace taylortrack

