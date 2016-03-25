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
* @brief Implementation of A Voice Activity Strategy
* @version 1
*/
#ifndef TAYLORTRACK_UTILS_VADSTRATEGY_H_
#define TAYLORTRACK_UTILS_VADSTRATEGY_H_

#include <complex.h>
#include <valarray>
#include <vector>

namespace taylortrack {
namespace utils {
typedef std::complex<double> ComplexDouble;
typedef std::valarray<double> RArray;
typedef std::valarray<ComplexDouble> CArray;
/**
* @class VadStrategy
* @brief Interface for Voice Activity Trackers with parsed samples
*/
class VadStrategy {
 public:
  /**
   * @brief tracks voice activity for a given sample
   * @param &sample
   * @return true if voice activity has been tracked in given sample
   */
  virtual bool detect(const RArray &sample) = 0;
};
}  // namespace utils
}  // namespace taylortrack

#endif  // TAYLORTRACK_UTILS_VADSTRATEGY_H
