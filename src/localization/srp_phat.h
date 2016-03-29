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
/**
 * @typedef Complex
 * Complex number type
 */
typedef std::complex<double> Complex;
/**
 * @typedef RArray
 * valarray filled with double values.
 */
typedef std::valarray<double> RArray;
/**
 * @typedef CArray
 * valarray filled with complex values.
 */
typedef std::valarray<Complex> CArray;
/**
* @class SrpPhat
* @brief Implements the speaker tracking functions from the AudioLocalizer interface.
*
* Strategy that implements SrpPhat to localize a speaker.
* @code
*  //Example usage:
*  // simply assign a srp class instance and assign the settings you wish to use
*  // afterwards tell the srp instance to use these settings with set_config
*
*  taylortrack::localization::SrpPhat srp;
*  taylortrack::utils::AudioSettings settings;
*  settings.beta = 0.7;
*  settings.sample_rate = 44100;
*  settings.grid_x = 4.0;
*  settings.grid_y = 4.0;
*  settings.interval = 0.1;
*  settings.mic_x = micsX;
*  settings.mic_y = micsY;
*  settings.frame_size = steps;
*
*  taylortrack::utils::ConfigParser config;
*  config.set_audio_settings(settings);
*
*  srp.set_config(config);
*  // some vector containing an RArray entry for each microphone channel you have
*  std::vector<taylortrack::utils::FftLib::RArray> signals;
*
*  // afterwards you can track people with get_position or other methods like this
*
*  int position = srp.get_position(signals);
* @endcode
*/
class SrpPhat : public Localizer {
 public:
  /**
   * @brief Standard constructor
   */
  SrpPhat() = default;
  /**
   * @brief Default Copy constructor
   * @param that object to be copied
   */
  SrpPhat(const SrpPhat &that) = default;
  /**
   * @var kSpeedOfSound
   * @brief Speed of Sound used for calculations within the class.
   */
  const double kSpeedOfSound = 340.42;
  /**
   * @var kPI
   * @brief PI constant used for caltulations within the class.
   */
  const double kPI = 3.141592653589793238460;
  /**
  * @brief Gets most likely position of the recorded speaker in degrees and a probability distribution
  * over angles and stores those values in appropiate class variables
  * @param  signals a vector of all microphone signals with each being a RArray
  */
  void calculate_position_and_distribution(const std::vector<RArray> &signals);

  /**
  * @brief Gets most likely position of the recorded speaker in degrees
  * @param  signals a vector of all microphone signals with each being a RArray
  * @return speaker position in degree
  */
  int get_position(const std::vector<RArray> &signals) override;

  /**
  * @brief Returns a probability distribution for the position of the speaker over all degrees
  * @param  signals a vector of all microphone signals with each being a RArray
  * @return A RArray with all probability values
  */
  RArray get_position_distribution(const std::vector<RArray> &signals) override;

  /**
  * @brief Returns an RAarray filled with values from a given filepath_name. Only works for one value per column
  * @param  filepath_name A string with the path to the file containing the values
  * @return RArray with all values in that file
  */
  RArray get_microphone_signal(const std::string &filepath_name);

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
  std::vector<std::tuple<int, int>> get_microphone_pairs();

  /**
  * @brief converts a 2 dimensional point in space to degree
  * @param x_coordinate x coordinate of a point in x y grid
  * @param y_coordinate y coordinate of a point in x y grid
  * @return speaker position in degree
  */
  int point_to_degree(double x_coordinate, double y_coordinate);

  /**
  * @brief Returns the expected delay of sound arrival given that the noise source stands at the given point
  * @param point The coordinates of the noise source
  * @param microphone1 coordinates of the first microphone
  * @param microphone2 coordinates of the second microphone
  * @return the expected delay in seconds
  */
  double inter_microphone_time_delay(const RArray &point, const RArray &microphone1, const RArray &microphone2);

  /**
  * @brief Returns the generalized cross correlation between two audio signals
  * @param signal1 first discrete audio signal
  * @param signal2 second discrete audio signal
  * @return returns the shifted cross correlation vector so that the end length has to be length(signal1)+ length(signal2) -1
  */
  RArray generalized_cross_correlation(const RArray &signal1, const RArray &signal2);

  /**
  * @brief Returns a x-y grid with the summed up gcc values for each point and each microphone pair
  * @param signals a vector with a variable amount of microphone signals. The amount of signals has to match the amount of stored microphones.
  * @return The GccGrid Matrix modeled as two nested vectors that contains every point of the room(grid) and the corresponding cross correlation value.
  */
  std::vector<std::vector<double>>
      get_generalized_cross_correlation(const std::vector<RArray> &signals);

  /**
   * @brief Returns values for a given axis
   * @param xaxis defines which axis you want values for xaxis=true means x axis and xaxis=false returns values for the y axis
   * @return A vector of all X-, or Y values of the grid depending on the specified axis,length of the axis and stepsize specified in the constructor.
   */
  std::vector<double> get_axis_values(bool xaxis);

  /**
   * @brief function that search for a specific val in a given valarray of doubles
   * @param in_vector RArray that contains values to be searched
   * @param value value to look for in the RArray
   * @return Returns index of the value in the RArray. If value is not found returns -1
   */
  int find_value(const RArray &in_vector, double value);
  /**
    * @brief Gets the audio samplerate the algorithm is working with
    * @return Returns the audio samplerate (samples per second)
    */
  int get_samplerate() const {
    return samplerate_;
  }
  /**
    * @brief Sets the audio samplerate the algorithm is working with
    * @param samplerate
    */
  void set_samplerate(int samplerate) {
    samplerate_ = samplerate;
  }
  /**
    * @brief Gets the length of the x axis used for the grid that models the room.
    * @return Returns the x axis length in meters
    */
  double get_x_length() const {
    return x_length_;
  }
  /**
     * @brief Sets the length of the x axis used for the grid that models the room.
     * @param x_length for setting the length
     */
  void set_x_length(double x_length) {
    x_length_ = x_length;
  }
  /**
    * @brief Gets the length of the y axis used for the grid that models the room.
    * @return Returns the y axis length in meters
    */
  double get_y_length() const {
    return y_length_;
  }
  /**
     * @brief Sets the length of the y axis used for the grid that models the room.
     * @param y_length for setting the length
     */
  void set_y_length(double y_length) {
    y_length_ = y_length;
  }
  /**
    * @brief Gets the stepsize resolution for points in the room.
    * @return Returns the stepsize in meters.
    */
  double get_step_size() const {
    return stepsize_;
  }
  /**
    * @brief Sets the stepsize resolution for points to be considered in the room. The lower the more points used.
    * @param stepsize for setting the stepsize
    */
  void set_step_size(double stepsize) {
    stepsize_ = stepsize;
  }
  /**
    * @brief Gets the x axis values of the microphones in the room(grid).
    * @return Returns a valarray with the corresponding x axis values of each microphone.
    */
  const RArray &get_x_dim_mics() const {
    return x_dim_mics_;
  }
  /**
    * @brief Sets the x axis values of the microphones in the room(grid).
    * @param x_dim_mics for setting the x values of the microphones
    */
  void set_x_dim_mics(const RArray &x_dim_mics) {
    x_dim_mics_ = x_dim_mics;
  }
  /**
    * @brief Gets the y axis values of the microphones in the room(grid).
    * @return Returns a valarray with the corresponding y axis values of each microphone.
    */
  const RArray &get_y_dim_mics() const {
    return y_dim_mics_;
  }
  /**
    * @brief Sets the y axis values of the microphones in the room(grid).
    * @param y_dim_mics for setting the y values of the microphones
    */
  void setY_dim_mics(const RArray &y_dim_mics) {
    y_dim_mics_ = y_dim_mics;
  }
  /**
    * @brief Gets the length of the audio signals the algorithm is working with.
    * @return Returns the number of samples per frame for which a localization estimation is done.
    */
  int get_steps() const {
    return steps_;
  }
  /**
    * @brief Sets the length of the audio signals the algorithm is working with (samples per frame).
    * @param steps for setting length of audio signal
    */
  void set_steps(int steps) {
    steps_ = steps;
  }
  /**
    * @brief Gets the beta exponent used in the cross correlation weighting.
    * @return Returns the beta exponent.
    */
  double get_beta() const {
    return beta_;
  }
    /**
    * @brief Sets the beta exponent used in the cross correlation weighting.
    * @param beta for setting beta exponent
    */
  void set_beta(double beta) {
    beta_ = beta;
  }
  /**
   * @brief Checks whether the algorithm has been properly initialized
   * by the config setter
   * @return true if the configuration has been properly initialized, false otherwise.
   */
  bool is_initialized(){
    return intialized_;
  }
  /**
   * @brief Returns the speaker position distribution of the last calculated frame.
   * @return the last calculated speaker position distribution
   */
  const RArray &get_last_distribution() const {
    return last_distribution_;
  }
  /**
   * @brief Returns the last calculated speaker position.
   * @return the calculated speaker position of the last frame
   */
  int get_last_position() const {
    return last_position_;
  }

  /**
  * @brief Sets all relevant parameters of the srp phat algorithm.
  * @param config object containing the configuration from a config file
  */
  void set_config(const taylortrack::utils::ConfigParser &config) override {
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
// last computed position distribution of the speaker;
  RArray last_distribution_ = RArray(360);
  // last computed position of the speaker
  int last_position_ = 0;
  // nested vector containing delays for each point in the considered space considering each microphone pair
  std::vector<std::vector<std::vector<double>>> delay_tensor_;
  // audio sample rate the algorithm should work with
  int samplerate_ = 0;
  // size of the grids x axis to consider for the estimation
  double x_length_ = 0.0;
  // size of the grids y axis to consider for the estimation
  double y_length_ = 0.0;
  // sample length or the amount of discrete signals
  // to consider for each estimate
  double stepsize_ = 0.0;
  // X coordinates of the microphones in the grid
  RArray x_dim_mics_;
  // Y coordinates of the microphones in the grid
  RArray y_dim_mics_;
  // steps The amount of sampled points an audio signal has
  // that needs to be evaluated.
  int steps_ = 0;
  // beta The exponent of the weighting term of the cross correlation.
  double beta_ = 0.0;
  // boolean to check if an object has been initialized
  bool intialized_ = false;
};
}  // namespace localization
}  // namespace taylortrack

#endif  // TAYLORTRACK_LOCALIZATION_SRPPHAT_H_
