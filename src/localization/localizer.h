#ifndef TAYLORTRACK_LOCALIZER_H
#define TAYLORTRACK_LOCALIZER_H

#include <vector>
#include <valarray>
#include "utils/config.h"
#include "utils/config_parser.h"

namespace taylortrack {
  namespace localization {
    typedef std::valarray<double> RArray;
    /**
    * @interface Localizer
    * @brief Interface for different localization algorithms.
    *
    * Localization algorithm that will get used
    */
    class Localizer {
     public:
      /**
      * @brief return suspected position of speaker in degrees.
      * @return angle position of speaker in audiofiles.
      */
      virtual int getPosition(const std::vector<RArray> &signals) = 0;

      /**
      * @brief Returns a probability distribution for the position of the speaker over all degrees
      * @param  signals a vector of all microphone signals
      * @return A RArray with all probability values
      */
      virtual RArray getPositionDistribution(const std::vector<RArray> &signals) = 0;

      /**
      * @brief Sets all relevant parameters of the implemented algorithm. Missing Parameters have to be placed inside
      *        the AudioSettings struct.
      * @param config taylortrack::utils::ConfigParser object for the algorithm to take its configuration
      * @pre taylortrack::utils::ConfigParser::is_valid() should return true
      */
      virtual void setConfig(const utils::ConfigParser &config) =0;
    };
  } // namespace localization
} // namespace taylortrack



#endif //TAYLORTRACK_AUDIO_LOCALIZER_H
