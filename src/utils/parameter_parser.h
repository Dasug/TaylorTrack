/**
 * @file
 * @brief Provides a parser for the start parameters.
 * @version 1
 */
#ifndef TAYLORTRACK_PARAMETER_PARSER_H
#define TAYLORTRACK_PARAMETER_PARSER_H
#include "parameters.h"
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
       * @return Returns file path, the size in which the packets shall be streamed, the port name and a valid flag.
       */
      static Parameters parse_streamer(int argc, const char **argv);
    };
  } // namespace utils
} // namespace taylortrack

#endif //TAYLORTRACK_PARAMETER_PARSER_H
