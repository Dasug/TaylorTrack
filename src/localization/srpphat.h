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
#include <complex>
#include <valarray>
#include <vector>
#include "audio_localizer.h"
namespace taylortrack {
    namespace localization {

        typedef std::valarray<double> RArray;
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
            * initializes the localization algorithm with all needed parameters
            * @param samplerate Audio samplerate (how many discrete signals per second).
            * @param samplelength Length of the sample that the algorithm will be fed with.
            * @param mics   Microphone positions in the room.
            */
            SrpPhat(const int samplerate, const int samplelength,const RArray &xDimMics,const RArray &yDimMics, const double xLength, const double yLength, const double stepSize);

            /**
            * @brief Returns most likely position of the recorded speaker in degrees
            * @param
            * @return speaker position in degree
            */
            const int getposition();

            /**
            * @brief Returns a tensor that contains the expected delay for each point in a x-y grid for all possible microphone pairs
            * @return Returns the delay tensor modelled by a 3 dimensional vector
            */
            std::vector<std::vector<std::vector<double>>> getDelayTensor();


            /**
            * @brief Returns a vector of tuples containing microphone pairs indices
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
            * @brief Returns the expected delay of sound arrival given that noise source stands at the given point
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
            RArray gcc(RArray &signal1, RArray &signal2,double beta);

        private:
            int samplerate_;
            int samplelength_;
            double xLength_;
            double yLength_;
            double stepSize_;
            RArray xDimMics_;
            RArray yDimMics_;
        };
    }
}



#endif //TAYLORTRACK_SRPPHAT_H
