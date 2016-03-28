/*
The MIT License (MIT)

Copyright (c) 2015 Marius Kaufmann, Tamara Frieß, Jannis Hoppe, Christian Hack

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/**
 * @file
 * @brief Provides a parser for the start parameters.
 */
#ifndef TAYLORTRACK_UTILS_PARAMETER_PARSER_H_
#define TAYLORTRACK_UTILS_PARAMETER_PARSER_H_
#include "utils/parameters.h"
namespace taylortrack {
namespace utils {
namespace parameter_parser {
/**
 * @brief Parameter Parser for the streaming module.
 *
 * @param argc Amount of passed parameters
 * @param argv Passed Parameters.
 * @return Returns file path, the size in which the packets shall be streamed, the port name and a valid flag.
 */
Parameters parse_streamer(int argc, const char **argv);
};
}  // namespace utils
}  // namespace taylortrack

#endif  // TAYLORTRACK_UTILS_PARAMETER_PARSER_H_

