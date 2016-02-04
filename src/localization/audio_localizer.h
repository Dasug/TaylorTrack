//
// Created by Jannis Hoppe on 29.01.16.
//

#ifndef TAYLORTRACK_AUDIO_LOCALIZER_H
#define TAYLORTRACK_AUDIO_LOCALIZER_H

namespace taylortrack {
    namespace localization {
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
            virtual const int getposition() = 0;

        };
    } // namespace input
} // namespace taylortrack



#endif //TAYLORTRACK_AUDIO_LOCALIZER_H
