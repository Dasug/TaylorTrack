//
// Created by Jannis Hoppe on 29.01.16.
//

#ifndef TAYLORTRACK_AUDIO_LOCALIZER_H
#define TAYLORTRACK_AUDIO_LOCALIZER_H
#include <vector>
#include <valarray>
namespace taylortrack {
    namespace localization {
        typedef std::valarray<double> RArray;
        /**
		* @interface AudioLocalizer
		* @brief Interface for different audio localization algorithms.
		*
		* Localization algorithm that will get used
        */
        class AudioLocalizer {
        public:
            /**
            * @brief return suspected position of speaker in degrees.
            * @return angle position of speaker in audiofiles.
            */
            virtual int getPosition(std::vector<std::vector<double>> &gccGrid) = 0;

            /**
            * @brief Returns a probability distribution for the position of the speaker over all degrees
            * @param  signals a vector of all microphone signals
            * @return A RArray with all probability values
            */
            virtual RArray getPositionDistribution(std::vector<std::vector<double>> &gccGrid) = 0;

        };
    } // namespace input
} // namespace taylortrack



#endif //TAYLORTRACK_AUDIO_LOCALIZER_H
