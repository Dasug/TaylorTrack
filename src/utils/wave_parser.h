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
* @brief Header file for taylortrack::utils::WaveParser class.
*/

#ifndef TAYLORTRACK_UTILS_WAVE_PARSER_H
#define TAYLORTRACK_UTILS_WAVE_PARSER_H

#include <fstream>
#include <iostream>
#include <string>

namespace taylortrack {
namespace utils {
/**
* @class WaveParser
* @brief Parses a wave file and extracts samples.
*
* Helper class to deal with .wav files. Parses the RIFF header and the wave chunk headers.
* However, it only extracts raw sample data and doesn't decode the samples.
*/
class WaveParser {
 public:
  /**
  * @brief Wave parser constructor
  *
  * Opens the supplied wave file and parses its header
  * @param file_name Path to the file to be parsed.
  */
  explicit WaveParser(const char *file_name);

  /**
   * @brief Default copy constructor
   */
  WaveParser(const WaveParser &that) = default;

  /**
  * @brief WaveParser Destructor
  *
  * Releases wave file
  */
  virtual ~WaveParser();

  /**
  * @brief Checks whether the parsed file has a correct header.
  * @return true if file is valid, otherwise false
  */
  bool is_valid() const;

  /**
  * @brief Gets the sample encoding format specified in the wave header
  * @pre is_valid() returns true
  * @return The audio format code
  * @sa %Audio format code reference: https://de.wikipedia.org/wiki/RIFF_WAVE#Datenformate_.28Format-Tag.29
  */
  int get_audio_format() const;

  /**
  * @brief Gets the number of audio channels within the parsed wave file
  * @pre is_valid() returns true
  * @return Number of channels
  */
  int get_num_channels() const;

  /**
  * @brief Gets the parsed wave file's sample rate
  * @pre is_valid() returns true
  * @return Sample rate (Samples / second)
  */
  int64_t get_sample_rate() const;

  /**
  * @brief Gets the parsed wave file's byte rate
  * @pre is_valid() returns true
  * @return Byte rate (Bytes / second)
  */
  int64_t get_byte_rate() const;

  /**
  * @brief Gets the parsed wave file's number of bytes per sample frame
  *
  * A sample frame refers to a single sample for every audio channel
  * @pre is_valid() returns true
  * @return Sample frame size in bytes
  */
  int get_block_align() const;

  /**
  * @brief Gets the parsed wave file's bits per sample
  * @pre is_valid() returns true
  * @return Number of Bits included in a single sample. Must be a multiple of 8
  */
  int get_bits_per_sample() const;

  /**
  * @brief Fetches the next n samples
  *
  * Keeps track of which samples have been extracted already and continues with the next n samples
  * Where n is the amount of samples supplied by the parameter sample_num.
  * If more samples are requested than remain unextracted, it will extract all remaining samples instead.
  * @pre is_valid() returns true
  * @param sample_num Number of samples to be extracted for each audio channel
  * @return String with raw binary data for all extracted samples. Exact encoding depends on audio format
  * @sa get_audio_format() for wave file's audio format
  */
  std::string get_samples(int64_t sample_num);

  /**
  * @brief Checks whether all samples have been extracted yet
  * @pre is_valid() returns true
  * @return true if all samples have been extracted, otherwise false
  */
  bool is_done();

  /**
  * @brief Gets the total number of samples
  * @pre is_valid() returns true
  * @return Total number of samples within parsed wave file
  */
  int64_t get_sample_num() const;
 private:
  // signals whether the parsed file has a correct header.
  bool valid_ = false;
  // specifies the audio sample encoding
  uint16_t audio_format_ = 0x0001;
  // specifies the amount of audio channels
  uint16_t num_channels_ = 1;
  // specifies the samplerate per second
  uint32_t sample_rate_ = 44100;
  // specifies the byterate per second
  uint32_t byte_rate_ = 88200;
  // the parsed wave file's number of bytes per sample frame
  uint16_t block_align_;
  // the parsed wave file's bits per sample
  uint16_t bits_per_sample_ = 16;
  // the parsed wave file's datasize
  uint32_t data_size_ = 0;
  // a stream of the wave file
  std::ifstream *file_;
  //
  std::fpos<mbstate_t> data_offset_;
  void parse_file();
};
}  // namespace utils
}  // namespace taylortrack

#endif  // TAYLORTRACK_UTILS_WAVE_PARSER_H
