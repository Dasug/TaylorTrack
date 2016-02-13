//
// Created by Jannis Hoppe on 29.01.16.
//

#ifndef TAYLORTRACK_SRPPHAT_H
#define TAYLORTRACK_SRPPHAT_H


/**
* @file
* @brief Implements the SRP PHAT algorithm
* @details
* @version 1
*/
#include "audio_localizer.h"
#include <complex>
#include <valarray>
#include <vector>
#include <fstream>

namespace taylortrack {
    namespace localization {
        typedef std::complex<double> Complex ;
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
            * @param samplerate Audio samplerate (how many discrete signals per second).
            * @param samplelength Length of the sample that the algorithm will be fed with.
            * @param mics   Microphone positions in the room.
            */
            SrpPhat(const int samplerate,const RArray &xDimMics,const RArray &yDimMics, const double xLength, const double yLength, const double stepSize,const int steps,double beta);

            /**
            * @brief Returns most likely position of the recorded speaker in degrees
            * @param
            * @return speaker position in degree
            */
            int getPosition(std::vector<std::vector<double>> &gccGrid);

            /**
            * @brief Returns a probability distribution for the position of the speaker over all degrees
            * @param  signals a vector of all microphone signals
            * @return A RArray with all probability values
            */
            RArray getPositionDistribution(std::vector<std::vector<double>> &gccGrid);

            /**
            * @brief Returns an RAarray with values filled in from a given file. Only works for one value per column
            * @param  s A string with the path to the file containing the values
            * @return RArray with all values in that file
            */
            RArray getMicSignal(const std::string &s);

            /**
            * @brief Returns a tensor that contains the expected delay for each point in a x-y grid for all possible microphone pairs
            * @return Returns the delay tensor modelled by a 3 dimensional vector
            */
            std::vector<std::vector<std::vector<double>>> getDelayTensor();


            /**
            * @brief Returns a vector of tuples containing all possible microphone pairs indices
            * @return vector of microphone pair tuples
            */

            std::vector< std::tuple<int,int>> getMicPairs();
            /**
            * @brief converts a 2 dimensional point in space to degree
            * @param x_coordinate x coordinate of a point in x y grid
            * @param y_coordinate y coordinate of a point in x y grid
            * @return speaker position in degree
            */
            int pointToAngle(double x_coordinate,double y_coordinate);

            /**
            * @brief Returns the expected delay of sound arrival given that the noise source stands at the given point
            * @param point The coordinates of the noise source
            * @param mic1 coordinates of the first microphone
            * @param mic2 coordinates of the second microphone
            * @return the expected delay in seconds
            */
            double imtdf(RArray &point,RArray &mic1, RArray &mic2);
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

            * @return Returns the gcc value grid as
            */
            std::vector<std::vector<double>> getGccGrid(std::vector<RArray> &signals);


            /**
             * @brief Returns values for a given axis
             * @param axis defines which axis you want values for xaxis=true means x axis and xaxis=false returns values for the y axis
             */
            std::vector<double> getAxisvalues(bool xaxis);

            /**
             * @brief simple find function for valarray of doubles
             * @param ra RArray that contains values to search
             * @param val value to look for in the RArray
             * @return Returns index of the value in the RArray in case the value was found -1 otherwise.
             */
            int findVal(RArray &ra,double val);

        private:
        public:
            int getSamplerate_() const {
                return samplerate_;
            }

            void setSamplerate_(int samplerate_) {
                SrpPhat::samplerate_ = samplerate_;
            }

            double getXLength_() const {
                return xLength_;
            }

            void setXLength_(double xLength_) {
                SrpPhat::xLength_ = xLength_;
            }

            double getYLength_() const {
                return yLength_;
            }

            void setYLength_(double yLength_) {
                SrpPhat::yLength_ = yLength_;
            }

            double getStepSize_() const {
                return stepSize_;
            }

            void setStepSize_(double stepSize_) {
                SrpPhat::stepSize_ = stepSize_;
            }

            const RArray &getXDimMics_() const {
                return xDimMics_;
            }

            void setXDimMics_(const RArray &xDimMics_) {
                SrpPhat::xDimMics_ = xDimMics_;
            }

            const RArray &getYDimMics_() const {
                return yDimMics_;
            }

            void setYDimMics_(const RArray &yDimMics_) {
                SrpPhat::yDimMics_ = yDimMics_;
            }

            int getSteps_() const {
                return steps_;
            }

            void setSteps_(int steps_) {
                SrpPhat::steps_ = steps_;
            }

            double getBeta_() const {
                return beta_;
            }

            void setBeta_(double beta_) {
                SrpPhat::beta_ = beta_;
            }

        private:
            int samplerate_;        // audio sample rate the algorithm should work with
            double xLength_;        // size of the grids x axis to consider for the estimation
            double yLength_;        // size of the grids y axis to consider for the estimation
            double stepSize_;       // sample length or the amount of discrete signals to consider for each estimate
            RArray xDimMics_;       // X coordinates of the microphones in the grid
            RArray yDimMics_;       // Y coordinates of the microphones in the grid
            int steps_;
            double beta_;
        };
    }
}



#endif //TAYLORTRACK_SRPPHAT_H
