/**
* @file
* @brief Implements the SRP PHAT algorithm
* @version 1
*/
#ifndef TAYLORTRACK_SRPPHAT_H
#define TAYLORTRACK_SRPPHAT_H

#include "audio_localizer.h"
#include <complex>
#include <valarray>
#include <vector>
#include <fstream>

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
    class SrpPhat: public AudioLocalizer {
     public:
      /**
      * @brief SrpPhat Constructor
      *
      * initializes the localization algorithm with all relevant parameters
      * @param samplerate Audio samplerate (amount of discrete signals per second).
      * @param x_dim_mics X coordinates of the microphones in the grid
      * @param y_dim_mics Y coordinates of the microphones in the grid
      * @param x_length Total length of the x axis in the grid
      * @param y_length Total length of the y axis in the grid
      * @param stepsize The resolution of the points to consider on each axis in the Grid. For instance a 2x2 meter grid with a stepsize of 0.1 considers the points (2,-2),(2,-1.9),(2,-1.8)...(-1.8,2),(-1.9,2),(-2,2)
      * @param steps The amount of sampled points an audio signal has that needs to be evaluated.
      * @param beta The exponent of the weighting term of the cross correlation.
      */
      SrpPhat(const int samplerate,
              const RArray &x_dim_mics,
              const RArray &y_dim_mics,
              const double x_length,
              const double y_length,
              const double stepsize,
              const int steps,
              double beta);

      /**
      * @brief Gets most likely position of the recorded speaker in degrees
      * @param gcc_grid Matrix modeled as two nested vectors that contains every point of the room(grid) and the corresponding cross correlation value.
      * @return speaker position in degree
      */
      int getPosition(std::vector<std::vector<double>> &gcc_grid);

      /**
      * @brief Returns a probability distribution for the position of the speaker over all degrees
      * @param  gcc_grid a vector of all microphone signals
      * @return A RArray with all probability values
      */
      RArray getPositionDistribution(std::vector<std::vector<double>> &gcc_grid);

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
      double imtdf(RArray &point, RArray &mic1, RArray &mic2);

      /**
      * @brief Returns the generalized cross correlation between two audio signals
      * @param signal1 first discrete audio signal
      * @param signal2 second discrete audio signal
      * @return returns the shifted cross correlation vector so that the end length has to be length(signal1)+ length(signal2) -1
      */
      RArray gcc(RArray &signal1, RArray &signal2);

      /**
      * @brief Returns a x-y grid with the summed up gcc values for each point and each microphone pair
      * @param signals a vector with a variable amount of microphone signals. The amount of signals has to match the amount of stored microphones.
      * @return The GccGrid Matrix modeled as two nested vectors that contains every point of the room(grid) and the corresponding cross correlation value.
      */
      std::vector<std::vector<double>> getGccGrid(std::vector<RArray> &signals);

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
      int findVal(RArray &ra, double val);

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
         * @para y_length for setting the length
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
        * @return Returns a valarray with the corresponding y axis values of each microphone.
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

     private:
      int samplerate_;          // audio sample rate the algorithm should work with
      double x_length_;         // size of the grids x axis to consider for the estimation
      double y_length_;         // size of the grids y axis to consider for the estimation
      double stepsize_;         // sample length or the amount of discrete signals to consider for each estimate
      RArray x_dim_mics_;       // X coordinates of the microphones in the grid
      RArray y_dim_mics_;       // Y coordinates of the microphones in the grid
      int steps_;               // steps The amount of sampled points an audio signal has that needs to be evaluated.
      double beta_;             // beta The exponent of the weighting term of the cross correlation.
    };
  } // namespace localization
} // namespace taylortrack

#endif //TAYLORTRACK_SRPPHAT_H
