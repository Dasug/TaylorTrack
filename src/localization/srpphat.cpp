//
// Created by Jannis Hoppe on 29.01.16.
//
const double c = 340.42;    // speed of sound constant
const double PI = 3.141592653589793238460;
#include "srpphat.h"
#include "../utils/fft_lib.h"
#include <cstdlib>
#include <math.h>
#include <vector>
#include <tuple>
namespace taylortrack {
    namespace localization {
        SrpPhat::SrpPhat(const int samplerate, const int samplelength, const RArray &xDimMics,const RArray &yDimMics,const double xLength, const double yLength, const double stepSize) {
            samplerate_ = samplerate;
            samplelength_ = samplelength;
            xDimMics_ = xDimMics;
            yDimMics_ = yDimMics;
            xLength_ = xLength;
            yLength_ = yLength;
            stepSize_ = stepSize;
        }

        double SrpPhat::imtdf(RArray &point, RArray &mic1, RArray &mic2) {
            return (std::sqrt(std::pow(point - mic1, 2).sum()) - std::sqrt(std::pow(point - mic2, 2).sum())) / c;
        }

        int SrpPhat::pointToAngle(double x_coordinate, double y_coordinate) {
            return round(fmod(((atan2(y_coordinate,x_coordinate) * 180 / PI)+360) ,360));
        }

        std::vector< std::tuple<int,int>> SrpPhat::getMicPairs(){
            std::vector< std::tuple<int,int>> pairs;
            for (int i=0; i <xDimMics_.size(); i++){
                for (int j=0;j<xDimMics_.size();j++){
                    if (j>i){
                        pairs.push_back(std::make_tuple(i,j));
                    }
                }
            }
            return pairs;
        }

        RArray SrpPhat::gcc(RArray &signal1, RArray &signal2,double beta){
            int corr_length = signal1.size()+signal2.size() -1;
            // bringing the signals into the right shape to work with the fftlib
            // first making them complex and pad with necessary zeros
            taylortrack::utils::FftLib::CArray tempsignal1 = taylortrack::utils::FftLib::converttocomp(signal1);
            taylortrack::utils::FftLib::CArray tempsignal2 = taylortrack::utils::FftLib::converttocomp(signal2);
            taylortrack::utils::FftLib::CArray csignal1 = taylortrack::utils::FftLib::zeropadding(tempsignal1,corr_length-signal1.size());
            taylortrack::utils::FftLib::CArray csignal2 = taylortrack::utils::FftLib::zeropadding(tempsignal2,corr_length-signal2.size());


            // perform FFT on the converted signals
            taylortrack::utils::FftLib::fft(csignal1);
            taylortrack::utils::FftLib::fft(csignal2);

            // computing nominator and denominator of the generalized cross correlation
            taylortrack::utils::FftLib::CArray nominator = csignal1 * csignal2.apply(std::conj);

            taylortrack::utils::FftLib::CArray denominator = std::pow(abs(nominator),beta);

            // reverse transfering to time domain
            taylortrack::utils::FftLib::CArray temp = nominator / denominator;

            taylortrack::utils::FftLib::ifft(temp);

            taylortrack::utils::FftLib::RArray result(temp.size());
            taylortrack::utils::FftLib::RArray temp3 = taylortrack::utils::FftLib::converttoreal(temp);

            taylortrack::utils::FftLib::fftshift(result, temp3);

            return result;
        }

        const int SrpPhat::getposition() {
            return 0;
        };

        std::vector<std::vector<std::vector<double>>> SrpPhat::getDelayTensor() {
            std::vector<std::vector<std::vector<double>>> delayTensor;
            std::vector<double> xAxisValues;
            std::vector<double> yAxisValues;

            int vectorSize = xLength_/stepSize_;
            double xStart = xLength_/2 * -1;
            double yStart = yLength_/2;
            while(xAxisValues.size()<=vectorSize){
                xAxisValues.push_back(xStart);
                yAxisValues.push_back(yStart);
                xStart += stepSize_;
                yStart -= stepSize_;
            }

            int depth = xDimMics_.size();
            delayTensor.resize(vectorSize);
            for (int i = 0; i < vectorSize; ++i) {
                delayTensor[i].resize(vectorSize);
                for (int j = 0; j < vectorSize; ++j)
                    delayTensor[i][j].resize(depth);
            }
            std::vector< std::tuple<int,int>> pairs = getMicPairs();

            // iterating over the grid
            for(int x=0;x<vectorSize;x++){
                for(int y=0;y<vectorSize;y++){
                    // iterating over microphone pairs
                    for(int i=0;i<xDimMics_.size();i++) {
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
                        mic1[0] = xDimMics_[index1];
                        mic1[1] = yDimMics_[index1];
                        mic2[0] = xDimMics_[index2];
                        mic2[1] = yDimMics_[index2];
                        double delay = imtdf(point,mic1,mic2);
                        delayTensor[x][y][i] = delay;
                    }
                }
            }
            // iterating over all microphone pairs
            return delayTensor;
        }
    }
}