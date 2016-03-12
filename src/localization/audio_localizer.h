#ifndef TAYLORTRACK_AUDIO_LOCALIZER_H
#define TAYLORTRACK_AUDIO_LOCALIZER_H

#include <vector>
#include <valarray>
#include "../utils/config.h"
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
      virtual int getPosition(std::vector<RArray> &signals) = 0;

      /**
      * @brief Returns a probability distribution for the position of the speaker over all degrees
      * @param  signals a vector of all microphone signals
      * @return A RArray with all probability values
      */
      virtual RArray getPositionDistribution(std::vector<RArray> &signals) = 0;

      /**
      * @brief Sets all relevant parameters of the implemented algorithm. Missing Parameters have to be placed inside
      *        the AudioSettings struct.
      * @param  settings a struct of type AudioSettings
      */
      virtual void setParams(taylortrack::utils::AudioSettings &settings) =0;
    };
  } // namespace localization
} // namespace taylortrack



#endif //TAYLORTRACK_AUDIO_LOCALIZER_H
