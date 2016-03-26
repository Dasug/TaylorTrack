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
 * @brief Implementation of srpphat.h
 */
const double kSpeedOfSound = 340.42;
const double kPI = 3.141592653589793238460;
#include "localization/srpphat.h"
#include <string>
#include <tuple>
#include <vector>
#include "utils/fft_lib.h"

namespace taylortrack {
namespace localization {
double SrpPhat::inter_microphone_time_delay(const RArray &point,
                                            const RArray &microphone1,
                                            const RArray &microphone2) {
  return (std::sqrt(std::pow(point - microphone1, 2).sum())
      - std::sqrt(std::pow(point - microphone2, 2).sum()))
      / kSpeedOfSound;
}

int SrpPhat::point_to_degree(double x_coordinate, double y_coordinate) {
  return static_cast<int>(round(fmod(((atan2(y_coordinate, x_coordinate)
      * 180 / kPI) + 360), 360.0)));
}

std::vector<std::tuple<int, int>> SrpPhat::get_microphone_pairs() {
  std::vector<std::tuple<int, int>> pairs;
  // iterating over microphones
  for (int i = 0; i < static_cast<int>(x_dim_mics_.size()); i++) {
    for (int j = 0; j < static_cast<int>(x_dim_mics_.size()); j++) {
      // only append pairs once and don't consider pairs of the same microphone
      if (j > i) {
        pairs.push_back(std::make_tuple(i, j));
      }
    }
  }
  return pairs;
}

RArray SrpPhat::generalized_cross_correlation(const RArray &signal1, const RArray &signal2) {
  size_t corr_length = signal1.size() + signal2.size() - 1;
  /* bringing the signals into the right shape to work with the fftlib
   first making them complex and pad with necessary zeros */
  taylortrack::utils::FftLib fft_obj = taylortrack::utils::FftLib();
  CArray tempsignal1 = fft_obj.convertToComplex(signal1);
  CArray tempsignal2 = fft_obj.convertToComplex(signal2);
  CArray csignal1 =
      fft_obj.zeroPadding(tempsignal1,
                          static_cast<int> (corr_length - signal1.size()));
  CArray csignal2 =
      fft_obj.zeroPadding(tempsignal2,
                          static_cast<int> (corr_length - signal2.size()));

  // perform FFT on the converted signals
  fft_obj.fft(csignal1);
  fft_obj.fft(csignal2);

  // computing nominator and denominator of the generalized cross correlation
  CArray nominator = csignal1 * csignal2.apply(std::conj);
  CArray denominator = std::pow(abs(nominator), static_cast<float>(beta_));

  // reverse transfering to time domain
  CArray temp = nominator / denominator;

  fft_obj.ifft(temp);

  RArray result(temp.size());
  RArray temp3 = fft_obj.convertToReal(temp);

  fft_obj.fftshift(temp3, result);

  return result;
}

std::vector<double> SrpPhat::get_axis_values(bool xaxis) {
  std::vector<double> axisValues;
  int vectorSize = static_cast<int>(
      xaxis ? x_length_ / stepsize_ + 1 : y_length_ / stepsize_ + 1);
  double axStart = xaxis ? x_length_ / 2 * -1 : y_length_ / 2;
  while (static_cast<int>(axisValues.size()) < vectorSize) {
    axisValues.push_back(axStart);
    axStart = xaxis ? axStart + stepsize_ : axStart - stepsize_;
  }
  return axisValues;
}

RArray SrpPhat::get_position_distribution(const std::vector<RArray> &signals) {
  std::vector<std::vector<double>> gcc_grid = get_generalized_cross_correlation(signals);
  RArray degreevalues(360);
  std::vector<double> xAxisValues = get_axis_values(true);
  std::vector<double> yAxisValues = get_axis_values(false);

  for (int i = 0; i < static_cast<int>(xAxisValues.size()); i++) {
    for (int j = 0; j < static_cast<int>(yAxisValues.size()); j++) {
      int degree = point_to_degree(xAxisValues[i], yAxisValues[j]);
      if (degree == 360)
        degree = 0;
      degreevalues[degree] += gcc_grid[i][j];
    }
  }
  // get maximum for normalization of values
  double res = degreevalues.sum();
  return degreevalues / res;
}

int SrpPhat::get_position(const std::vector<RArray> &signals) {
  std::vector<std::vector<double>> gcc_grid = get_generalized_cross_correlation(signals);
  RArray degree_values(360);
  std::vector<double> xAxisValues = get_axis_values(true);
  std::vector<double> yAxisValues = get_axis_values(false);
  for (int i = 0; i < 360; i++) {
    degree_values[i] = 0;
  }
  int vectorSize = static_cast<int> (x_length_ / stepsize_ + 1);
  for (int i = 0; i < vectorSize; i++) {
    for (int j = 0; j < vectorSize; j++) {
      int degree = point_to_degree(xAxisValues[j],
                                   static_cast<double> (yAxisValues[i]));
      if (degree == 360)
        degree = 0;
      degree_values[degree] += gcc_grid[j][i];
    }
  }
  double res = degree_values.max();
  return find_value(degree_values, res);
}

int SrpPhat::find_value(const RArray &in_vector, double value) {
  for (int i = 0; i < static_cast<int>(in_vector.size()); i++) {
    if (std::abs(in_vector[i] - value) < 0.0001) {
      return i;
    }
  }
  return -1;
}

std::vector<std::vector<double>>
SrpPhat::get_generalized_cross_correlation(const std::vector<RArray> &signals) {
  std::vector<std::tuple<int, int>> pairs = get_microphone_pairs();
  std::vector<std::vector<double>> generalized_cross_correlation_values;
  int64_t vectorSize = int64_t(x_length_ / stepsize_ + 1);
  // initializing the gcc grid
  generalized_cross_correlation_values.resize(static_cast<unsigned long>(vectorSize));
  for (int i = 0; i < vectorSize; ++i) {
    generalized_cross_correlation_values[i].resize(static_cast<unsigned long>(vectorSize));
  }
  std::vector<std::vector<std::vector<double>>> micDelays = delay_tensor_;
  // iterating over all microphone pairs
  for (int i = 0; i < static_cast<int>(pairs.size()); i++) {
    int index1 = std::get<0>(pairs[i]);
    int index2 = std::get<1>(pairs[i]);
    // assigning the corresponding signals
    RArray signal1 = signals[index1];
    RArray signal2 = signals[index2];
    // get the current frame from the complete signal
    RArray signalSlice1 = signal1[std::slice(0, static_cast<size_t>(steps_ + 1), 1)];
    RArray signalSlice2 = signal2[std::slice(0, static_cast<size_t>(steps_), 1)];
    // computing the cross correlation of both frames
    RArray generalized_cross_temp = generalized_cross_correlation(signalSlice1, signalSlice2);
    // iterating over the whole x-y grid
    for (int x = 0; x < vectorSize; x++) {
      for (int y = 0; y < vectorSize; y++) {
        double delay = micDelays[x][y][i];
        // adding the corresponding cross correlation value to the grid
        generalized_cross_correlation_values[x][y] += generalized_cross_temp[(steps_ - 1) +
            round(delay / (1.0 / samplerate_))];
      }
    }
  }
  return generalized_cross_correlation_values;
}

std::vector<std::vector<std::vector<double>>> SrpPhat::get_delay_tensor() {
  std::vector<std::vector<std::vector<double>>> delay_tensor;
  std::vector<double> xAxisValues = get_axis_values(true);
  std::vector<double> yAxisValues = get_axis_values(false);
  std::vector<std::tuple<int, int>> pairs = get_microphone_pairs();
  int vector_size = x_length_ / stepsize_ + 1;
  int depth = pairs.size();
  delay_tensor.resize(vector_size);
  for (int i = 0; i < vector_size; ++i) {
    delay_tensor[i].resize(vector_size);
    for (int j = 0; j < vector_size; ++j)
      delay_tensor[i][j].resize(depth);
  }
  // iterating over the grid
  for (int x = 0; x < vector_size; x++) {
    for (int y = 0; y < vector_size; y++) {
      // iterating over microphone pairs
      for (int i = 0; i < static_cast<int>(pairs.size()); i++) {
        //
        RArray point(2);
        RArray microphone1(2);
        RArray microphone2(2);
        // assigning the current point in the grid
        point[0] = xAxisValues[x];
        point[1] = yAxisValues[y];
        // assigning the microphone values
        int index1 = std::get<0>(pairs[i]);
        int index2 = std::get<1>(pairs[i]);
        microphone1[0] = x_dim_mics_[index1];
        microphone1[1] = y_dim_mics_[index1];
        microphone2[0] = x_dim_mics_[index2];
        microphone2[1] = y_dim_mics_[index2];
        double delay = inter_microphone_time_delay(point, microphone1, microphone2);
        delay_tensor[x][y][i] = delay;
      }
    }
  }
  // iterating over all microphone pairs
  return delay_tensor;
}

RArray SrpPhat::get_microphone_signal(const std::string &filepath_name) {
  std::vector<double> temporary_vector;
  std::ifstream infile(filepath_name);
  std::string line = "";
  while (std::getline(infile, line)) {
    std::istringstream string_stream(line);
    double temporary_value;
    if (!(string_stream >> temporary_value))
      break;
    temporary_vector.push_back(temporary_value);
  }
  infile.close();
  RArray signal(temporary_vector.size());
  for (int i = 0; i < static_cast<int>(temporary_vector.size()); i++) {
    signal[i] = temporary_vector[i];
  }
  return signal;
}
}  // namespace localization
}  // namespace taylortrack
