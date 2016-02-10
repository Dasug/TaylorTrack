/**
* @file
* @brief Header file for taylortrack::utils::WaveParser class.
* @version 1
*/

#ifndef TAYLORTRACK_WAVE_PARSER_H
#define TAYLORTRACK_WAVE_PARSER_H

#include <fstream>
#include <iostream>

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
        private:
            bool valid = false;
            unsigned short audio_format;
            unsigned short num_channels = 1;
            unsigned long sample_rate;
            unsigned long byte_rate;
            unsigned short block_align;
            unsigned short bits_per_sample;
            unsigned long data_size;
            std::ifstream *file_;
            std::fpos<mbstate_t> data_offset;
            void parse_file();

        public:
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
            unsigned short get_audio_format() const;

            /**
            * @brief Gets the number of audio channels within the parsed wave file
            * @pre is_valid() returns true
            * @return Number of channels
            */
            unsigned short get_num_channels() const;

            /**
            * @brief Gets the parsed wave file's sample rate
            * @pre is_valid() returns true
            * @return Sample rate (Samples / second)
            */
            unsigned long get_sample_rate() const;

            /**
            * @brief Gets the parsed wave file's byte rate
            * @pre is_valid() returns true
            * @return Byte rate (Bytes / second)
            */
            unsigned long get_byte_rate() const;

            /**
            * @brief Gets the parsed wave file's number of bytes per sample frame
            * A sample frame refers to a single sample for every audio channel
            * @pre is_valid() returns true
            * @return Sample frame size in bytes
            */
            unsigned short get_block_align() const;

            /**
            * @brief Gets the parsed wave file's bits per sample
            * @pre is_valid() returns true
            * @return Number of Bits included in a single sample. Must be a multiple of 8
            */
            unsigned short get_bits_per_sample() const;


            /**
            * @brief Wave parser constructor
            * Opens the supplied wave file and parses its header
            * @param file_name Path to the file to be parsed.
            */
            WaveParser(const char *file_name);

            /**
            * @brief Fetches the next n samples
            * Keeps track of which samples have been extracted already and continues with the next n samples
            * If more samples are requested than remain unextracted, it will extract all remaining samples instead.
            * @pre is_valid() returns true
            * @param sample_num Number of samples to be extracted for each audio channel
            * @return String with raw binary data for all extracted samples. Exact encoding depends on audio format
            * @sa get_audio_format() for wave file's audio format
            */
            std::string get_samples(unsigned int sample_num);

            /**
            * @brief WaveParser Destructor
            * Releases wave file
            */
            virtual ~WaveParser();

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
            unsigned long get_sample_num();
        };
    } // namespace utils
} // namespace taylortrack

#endif //TAYLORTRACK_WAVE_PARSER_H
