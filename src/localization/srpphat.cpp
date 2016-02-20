  /**
  * @file
  * @brief Implementation of srpphat.h
  **/
const double kSpeedOfSound = 340.42;
const double kPI = 3.141592653589793238460;

#include "srpphat.h"
#include <tuple>
#include "../utils/fft_lib.h"

namespace taylortrack {
  namespace localization {
    SrpPhat::SrpPhat(const int samplerate,
                     const RArray &x_dim_mics,
                     const RArray &y_dim_mics,
                     const double x_length,
                     const double y_length,
                     double stepsize,
                     int steps,
                     double beta) {
      samplerate_ = samplerate;
      x_dim_mics_ = x_dim_mics;
      y_dim_mics_ = y_dim_mics;
      x_length_ = x_length;
      y_length_ = y_length;
      stepsize_ = stepsize;
      steps_ = steps;
      beta_ = beta;
    }

    double SrpPhat::imtdf(RArray &point, RArray &mic1, RArray &mic2) {
      return (std::sqrt(std::pow(point - mic1, 2).sum()) - std::sqrt(std::pow(point - mic2, 2).sum())) / kSpeedOfSound;
    }

    int SrpPhat::pointToDegree(double x_coordinate, double y_coordinate) {
      return (int) round(fmod(((atan2(y_coordinate, x_coordinate) * 180 / kPI) + 360), 360.0));
    }

    std::vector<std::tuple<int, int>> SrpPhat::getMicPairs() {
      std::vector<std::tuple<int, int>> pairs;
      // iterating over microphones
      for (int i = 0; i < x_dim_mics_.size(); i++) {
        for (int j = 0; j < x_dim_mics_.size(); j++) {
          // only append pairs once and don't consider pairs of the same microphone
          if (j > i) {
            pairs.push_back(std::make_tuple(i, j));
          }
        }
      }
      return pairs;
    }

    RArray SrpPhat::gcc(RArray &signal1, RArray &signal2) {
      size_t corr_length = signal1.size() + signal2.size() - 1;
      /* bringing the signals into the right shape to work with the fftlib
       first making them complex and pad with necessary zeros */
      taylortrack::utils::FftLib fft_obj = taylortrack::utils::FftLib();
      CArray tempsignal1 = fft_obj.convertToComplex(signal1);
      CArray tempsignal2 = fft_obj.convertToComplex(signal2);
      CArray csignal1 = fft_obj.zeroPadding(tempsignal1, (int) (corr_length - signal1.size()));
      CArray csignal2 = fft_obj.zeroPadding(tempsignal2, (int) (corr_length - signal2.size()));

      // perform FFT on the converted signals
      fft_obj.fft(csignal1);
      fft_obj.fft(csignal2);

      // computing nominator and denominator of the generalized cross correlation
      CArray nominator = csignal1 * csignal2.apply(std::conj);
      CArray denominator = std::pow(abs(nominator), (float) beta_);

      // reverse transfering to time domain
      CArray temp = nominator / denominator;

      fft_obj.ifft(temp);

      RArray result(temp.size());
      RArray temp3 = fft_obj.convertToReal(temp);

      fft_obj.fftshift(result, temp3);

      return result;
    }

    std::vector<double> SrpPhat::getAxisvalues(bool xaxis) {
      std::vector<double> axisValues;
      int vectorSize = (int) (xaxis ? x_length_ / stepsize_ + 1 : y_length_ / stepsize_ + 1);
      double axStart = xaxis ? x_length_ / 2 * -1 : y_length_ / 2;
      while (axisValues.size() < vectorSize) {
        axisValues.push_back(axStart);
        axStart = xaxis ? axStart + stepsize_ : axStart - stepsize_;
      }
      return axisValues;
    }

    RArray SrpPhat::getPositionDistribution(std::vector<std::vector<double>> &gcc_grid) {
      RArray degreevals(360);
      std::vector<double> xAxisValues = getAxisvalues(true);
      std::vector<double> yAxisValues = getAxisvalues(false);

      for (int i = 0; i < xAxisValues.size(); i++) {
        for (int j = 0; j < yAxisValues.size(); j++) {
          int deg = pointToDegree(xAxisValues[i], yAxisValues[j]);
          if (deg == 360)
            deg = 0;
          degreevals[deg] += gcc_grid[i][j];
        }
      }
      // get maximum for normalization of values
      double res = degreevals.sum();
      return degreevals / res;
    };

    int SrpPhat::getPosition(std::vector<std::vector<double>> &gcc_grid) {
      RArray degreevals(360);
      std::vector<double> xAxisValues = getAxisvalues(true);
      std::vector<double> yAxisValues = getAxisvalues(false);
      for (int i = 0; i < 360; i++) {
        degreevals[i] = 0;
      }
      int vectorSize = (int) (x_length_ / stepsize_ + 1);
      for (int i = 0; i < vectorSize; i++) {
        for (int j = 0; j < vectorSize; j++) {
          int deg = pointToDegree(xAxisValues[j], (double) yAxisValues[i]);
          if (deg == 360)
            deg = 0;
          degreevals[deg] += gcc_grid[j][i];
        }
      }
      double res = degreevals.max();
      return findVal(degreevals, res);
    };

    int SrpPhat::findVal(RArray &ra, double val) {
      for (int i = 0; i < ra.size(); i++) {
        if (std::abs(ra[i] - val) < 0.0001) {
          return i;
        }
      }
      return -1;
    }

    std::vector<std::vector<double>> SrpPhat::getGccGrid(std::vector<RArray> &signals) {
      std::vector<std::tuple<int, int>> pairs = getMicPairs();
      std::vector<std::vector<double>> gccValues;
      unsigned long vectorSize = (unsigned long) (x_length_ / stepsize_ + 1);
      // initializing the gcc grid
      gccValues.resize(vectorSize);
      for (int i = 0; i < vectorSize; ++i) {
        gccValues[i].resize(vectorSize);
      }

      size_t signalLength = signals[0].size();
      long steps = signalLength / steps_ + 1;
      std::vector<std::vector<std::vector<double>>> micDelays = get_delay_tensor();
      // iterating over all microphone pairs
      for (int i = 0; i < pairs.size(); i++) {
        RArray mic1(2);
        RArray mic2(2);
        int index1 = std::get<0>(pairs[i]);
        int index2 = std::get<1>(pairs[i]);
        // getting the coordinates of the mic pair
        mic1[0] = x_dim_mics_[index1];
        mic1[1] = y_dim_mics_[index1];
        mic2[0] = x_dim_mics_[index2];
        mic2[1] = y_dim_mics_[index2];
        // assigning the corresponding signals
        RArray signal1 = signals[index1];
        RArray signal2 = signals[index2];
        // get the current frame from the complete signal
        RArray signalSlice1 = signal1[std::slice(0, steps_ + 1, 1)];
        RArray signalSlice2 = signal2[std::slice(0, steps_, 1)];
        // computing the cross correlation of both frames
        int temp = signalSlice1.size();
        int temp2 = signalSlice2.size();
        RArray gccTemp = gcc(signalSlice1, signalSlice2);
        // iterating over the whole x-y grid
        for (int x = 0; x < vectorSize; x++) {
          for (int y = 0; y < vectorSize; y++) {
            double del = micDelays[x][y][i];
            // adding the corresponding cross correlation value to the grid
            gccValues[x][y] += gccTemp[(steps_ - 1) + round(del / (1.0 / samplerate_))];
          }
        }
      }
      return gccValues;
    }

    std::vector<std::vector<std::vector<double>>> SrpPhat::get_delay_tensor() {
      std::vector<std::vector<std::vector<double>>> delayTensor;
      std::vector<double> xAxisValues = getAxisvalues(true);
      std::vector<double> yAxisValues = getAxisvalues(false);
      std::vector<std::tuple<int, int>> pairs = getMicPairs();
      int vectorSize = x_length_ / stepsize_ + 1;

      int depth = pairs.size();
      delayTensor.resize(vectorSize);
      for (int i = 0; i < vectorSize; ++i) {
        delayTensor[i].resize(vectorSize);
        for (int j = 0; j < vectorSize; ++j)
          delayTensor[i][j].resize(depth);
      }

      // iterating over the grid
      for (int x = 0; x < vectorSize; x++) {
        for (int y = 0; y < vectorSize; y++) {
          // iterating over microphone pairs
          for (int i = 0; i < pairs.size(); i++) {
            //
            RArray point(2);
            RArray mic1(2);
            RArray mic2(2);
            // assigning the current point in the grid
            point[0] = xAxisValues[x];
            point[1] = yAxisValues[y];
            // assigning the microphone values
            int index1 = std::get<0>(pairs[i]);
            int index2 = std::get<1>(pairs[i]);
            mic1[0] = x_dim_mics_[index1];
            mic1[1] = y_dim_mics_[index1];
            mic2[0] = x_dim_mics_[index2];
            mic2[1] = y_dim_mics_[index2];
            double delay = imtdf(point, mic1, mic2);
            delayTensor[x][y][i] = delay;
          }
        }
      }
      // iterating over all microphone pairs
      return delayTensor;
    }

    RArray SrpPhat::getMicSignal(const std::string &filepath_name) {
      std::vector<double> tmp;
      std::ifstream infile(filepath_name);
      std::string line;
      while (std::getline(infile, line)) {
        std::istringstream ss(line);

        double a;
        if (!(ss >> a))
          break;

        tmp.push_back(a);
      }
      infile.close();
      RArray signal(tmp.size());
      for (int i = 0; i < tmp.size(); i++) {
        signal[i] = tmp[i];
      }
      return signal;
    }
  } // namespace localization
} // namespace taylortrack