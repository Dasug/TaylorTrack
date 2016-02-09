//
// Created by dasug on 05.02.16.
//

#ifndef TAYLORTRACK_WAVE_PARSER_H
#define TAYLORTRACK_WAVE_PARSER_H

#include <fstream>
#include <iostream>

namespace taylortrack {
    namespace utils {
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
            bool is_valid() const {
                return valid;
            }

            unsigned short get_audio_format() const {
                return audio_format;
            }

            unsigned short get_num_channels() const {
                return num_channels;
            }

            unsigned long get_sample_rate() const {
                return sample_rate;
            }

            unsigned long get_byte_rate() const {
                return byte_rate;
            }

            unsigned short get_block_align() const {
                return block_align;
            }

            unsigned short get_bits_per_sample() const {
                return bits_per_sample;
            }

            WaveParser(const char *file_name);

            std::string get_samples(unsigned int sample_num);

            virtual ~WaveParser();

            bool is_done();

            unsigned long get_sample_num();
        };
    } // namespace utils
} // namespace taylortrack

#endif //TAYLORTRACK_WAVE_PARSER_H
