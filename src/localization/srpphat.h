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
* @brief Implements the SRP PHAT algorithm
* @version 1
*/
#ifndef TAYLORTRACK_LOCALIZATION_SRPPHAT_H_
#define TAYLORTRACK_LOCALIZATION_SRPPHAT_H_
#include <complex>
#include <fstream>
#include <string>
#include <tuple>
#include <valarray>
#include <vector>
#include "localization/localizer.h"
#include "utils/config_parser.h"

namespace taylortrack {
namespace localization {
typedef std::complex<double> Complex;
typedef std::valarray<double> RArray;
typedef std::valarray<Complex> CArray;
/**
* @class SrpPhat
* @brief Implements the getposition function from the AudioLocalizer interface.
*
* Strategy that implements SrpPhat to localize a speaker.
*/
class SrpPhat: public Localizer {
 public:
  /**
  * @brief Gets most likely position of the recorded speaker in degrees
  * @param gcc_grid Matrix modeled as two nested vectors that contains every point of the room(grid) and the corresponding cross correlation value.
  * @return speaker position in degree
  */
  int getPosition(const std::vector<RArray> &signals);

  /**
  * @brief Returns a probability distribution for the position of the speaker over all degrees
  * @param  gcc_grid a vector of all microphone signals
  * @return A RArray with all probability values
  */
  RArray getPositionDistribution(const std::vector<RArray> &signals);

  /**
  * @brief Returns an RAarray filled with values from a given filepath_name. Only works for one value per column
  * @param  filepath_name A string with the path to the file containing the values
  * @return RArray with all values in that file
  */
  RArray getMicSignal(const std::string &filepath_name);

  /**
  * @brief Returns a tensor containing all delays for all possible microphone pairs.
  * @details Returns a (X,Y,Z) tensor with matrices modelling the room(X,Y) with each entry containing the appropriate delay for that point given a certain microphone pair. The third dimension(Z) of the tensor models all the possible microphone pairs.
  * @return Returns the delay tensor modelled by a 3 dimensional vector
  */
  std::vector<std::vector<std::vector<double>>> get_delay_tensor();


  /**
  * @brief Returns a vector of tuples containing all possible microphone pairs indices
  * @return vector of microphone pair tuples
  */
  std::vector<std::tuple<int, int>> getMicPairs();

  /**
  * @brief converts a 2 dimensional point in space to degree
  * @param x_coordinate x coordinate of a point in x y grid
  * @param y_coordinate y coordinate of a point in x y grid
  * @return speaker position in degree
  */
  int pointToDegree(double x_coordinate, double y_coordinate);

  /**
  * @brief Returns the expected delay of sound arrival given that the noise source stands at the given point
  * @param point The coordinates of the noise source
  * @param mic1 coordinates of the first microphone
  * @param mic2 coordinates of the second microphone
  * @return the expected delay in seconds
  */
  double imtdf(const RArray &point, const RArray &mic1, const RArray &mic2);

  /**
  * @brief Returns the generalized cross correlation between two audio signals
  * @param signal1 first discrete audio signal
  * @param signal2 second discrete audio signal
  * @return returns the shifted cross correlation vector so that the end length has to be length(signal1)+ length(signal2) -1
  */
  RArray gcc(const RArray &signal1, const RArray &signal2);

  /**
  * @brief Returns a x-y grid with the summed up gcc values for each point and each microphone pair
  * @param signals a vector with a variable amount of microphone signals. The amount of signals has to match the amount of stored microphones.
  * @return The GccGrid Matrix modeled as two nested vectors that contains every point of the room(grid) and the corresponding cross correlation value.
  */
  std::vector<std::vector<double>>
      getGccGrid(const std::vector<RArray> &signals);

  /**
   * @brief Returns values for a given axis
   * @param axis defines which axis you want values for xaxis=true means x axis and xaxis=false returns values for the y axis
   * @return A vector of all X-, or Y values of the grid depending on the specified axis,length of the axis and stepsize specified in the constructor.
   */

  std::vector<double> getAxisvalues(bool xaxis);

  /**
   * @brief function that search for a specific val in a given valarray of doubles
   * @param ra RArray that contains values to be searched
   * @param val value to look for in the RArray
   * @return Returns index of the value in the RArray. If value is not found returns -1
   */
  int findVal(const RArray &ra, double val);

    /**
    * @brief Gets the audio samplerate the algorithm is working with
    * @return Returns the audio samplerate (samples per second)
    */
  int getSamplerate() const {
    return samplerate_;
  }
    /**
    * @brief Sets the audio samplerate the algorithm is working with
    * @param samplerate
    */
  void setSamplerate(int samplerate) {
    SrpPhat::samplerate_ = samplerate;
  }
    /**
    * @brief Gets the length of the x axis used for the grid that models the room.
    * @return Returns the x axis length in meters
    */
  double getXLength() const {
    return x_length_;
  }
    /**
     * @brief Sets the length of the x axis used for the grid that models the room.
     * @param x_length for setting the length
     */
  void setXLength(double x_length) {
    SrpPhat::x_length_ = x_length;
  }
    /**
    * @brief Gets the length of the y axis used for the grid that models the room.
    * @return Returns the y axis length in meters
    */
  double getYLength() const {
    return y_length_;
  }
    /**
     * @brief Sets the length of the y axis used for the grid that models the room.
     * @param y_length for setting the length
     */
  void setYLength(double y_length) {
    SrpPhat::y_length_ = y_length;
  }
    /**
    * @brief Gets the stepsize resolution for points in the room.
    * @return Returns the stepsize in meters.
    */
  double getStepSize() const {
    return stepsize_;
  }
    /**
    * @brief Sets the stepsize resolution for points to be considered in the room. The lower the more points used.
    * @param stepsize for setting the stepsize
    */
  void setStepSize(double stepsize) {
    SrpPhat::stepsize_ = stepsize;
  }
    /**
    * @brief Gets the x axis values of the microphones in the room(grid).
    * @return Returns a valarray with the corresponding x axis values of each microphone.
    */
  const RArray &getXDimMics() const {
    return x_dim_mics_;
  }
    /**
    * @brief Sets the x axis values of the microphones in the room(grid).
    * @param x_dim_mics for setting the x values of the microphones
    */
  void setXDimMics(const RArray &x_dim_mics) {
    SrpPhat::x_dim_mics_ = x_dim_mics;
  }
    /**
    * @brief Gets the y axis values of the microphones in the room(grid).
    * @return Returns a valarray with the corresponding y axis values of each microphone.
    */
  const RArray &getYDimMics() const {
    return y_dim_mics_;
  }
    /**
    * @brief Sets the y axis values of the microphones in the room(grid).
    * @param y_dim_mics for setting the y values of the microphones
    */
  void setYDimMics(const RArray &y_dim_mics) {
    SrpPhat::y_dim_mics_ = y_dim_mics;
  }
    /**
    * @brief Gets the length of the audio signals the algorithm is working with.
    * @return Returns the number of samples per frame for which a localization estimation is done.
    */
  int getSteps() const {
    return steps_;
  }
    /**
    * @brief Sets the length of the audio signals the algorithm is working with (samples per frame).
    * @param steps for setting length of audio signal
    */
  void setSteps(int steps) {
    SrpPhat::steps_ = steps;
  }
    /**
    * @brief Gets the beta exponent used in the cross correlation weighting.
    * @return Returns the beta exponent.
    */
  double getBeta() const {
    return beta_;
  }
    /**
    * @brief Sets the beta exponent used in the cross correlation weighting.
    * @param beta for setting beta exponent
    */
  void setBeta(double beta) {
    SrpPhat::beta_ = beta;
  }

  bool is_initialized(){
    return intialized_;
  }

  /**
  * @brief Sets all relevant parameters of the srp phat algorithm.
  * @param  settings a struct of type AudioSettings
  */
  void setConfig(const taylortrack::utils::ConfigParser &config) {
    utils::AudioSettings audioConfig = config.get_audio_configuration();
    samplerate_ = audioConfig.sample_rate;
    x_length_ = audioConfig.grid_x;
    y_length_ = audioConfig.grid_y;
    stepsize_ = audioConfig.interval;
    x_dim_mics_ = audioConfig.mic_x;
    y_dim_mics_ = audioConfig.mic_y;
    steps_ = audioConfig.frame_size;
    beta_ = audioConfig.beta;
    delay_tensor_ = get_delay_tensor();
    intialized_ = true;
  }

 private:
  std::vector<std::vector<std::vector<double>>> delay_tensor_;
  // audio sample rate the algorithm should work with
  int samplerate_ = 0;
  // size of the grids x axis to consider for the estimation
  double x_length_ = 0;
  // size of the grids y axis to consider for the estimation
  double y_length_ = 0;
  // sample length or the amount of discrete signals
  // to consider for each estimate
  double stepsize_ = 0;
  // X coordinates of the microphones in the grid
  RArray x_dim_mics_;
  // Y coordinates of the microphones in the grid
  RArray y_dim_mics_;
  // steps The amount of sampled points an audio signal has
  // that needs to be evaluated.
  int steps_ = 0;
  // beta The exponent of the weighting term of the cross correlation.
  double beta_ = 0;
  // boolean to check if an object has been initialized
  bool intialized_ = false;
};
}  // namespace localization
}  // namespace taylortrack

#endif  // TAYLORTRACK_LOCALIZATION_SRPPHAT_H_
