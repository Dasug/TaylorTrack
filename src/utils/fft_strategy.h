//
// Created by Jannis Hoppe on 10.02.16.
//

#ifndef TAYLORTRACK_FFT_STRATEGY_H
#define TAYLORTRACK_FFT_STRATEGY_H

#include <vector>
#include <valarray>
namespace taylortrack {
    namespace utils {
        typedef std::valarray<double> RArray;
        typedef std::valarray<double> CArray;
        /**
		* @interface AudioLocalizer
		* @brief Interface for different audio localization algorithms.
		*
		* Localization algorithm that will get used
        */
        class fft_strategy {
        public:
            /**
            * @brief Perform a fast fourier transformation on a signal inplace
            * @param x Discrete audio signal.
            */
            virtual void fft(CArray &x) = 0;

            /**
            * @brief Perform an inverse fast fourier transformation on a signal inplace
            * @param x A Discrete audio signal to which a fft has been applied.
            */
            virtual void ifft(CArray &x) = 0;

            /**
            * @brief Perform a fftshift on a given signal.
            * @param outvec The valarray that has to contain the shifted signal.
            * @param invec The valarray that contains the signal that has to be shifted.
            */
            static void fftshift(RArray &outvec, RArray &invec);
        };
    } // namespace utils
} // namespace taylortrack



#endif //TAYLORTRACK_FFT_STRATEGY_H
