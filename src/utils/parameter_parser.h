/**
 * @file
 * @brief Provides a parser for the start parameters.
 */
#ifndef TAYLORTRACK_PARAMETER_PARSER_H
#define TAYLORTRACK_PARAMETER_PARSER_H
#include <tuple>
namespace taylortrack {
  namespace utils {

  /**
   * @class ParameterParser
   * @brief Provides parser for the start parameters.
   */
  class ParameterParser {
    public:
      /**
       * @brief Parser for the streaming module.
       *
       * @param argc Amount of passed parameters
       * @param argv Passed Parameters.
       * @return Returns file path and the size in which the packets shall be streamed.
       */
      static std::tuple<const char*,int> parse_streamer(int argc, const char **arg);
    };
  } // utils
} // Taylortrack

#endif //TAYLORTRACK_PARAMETER_PARSER_H
