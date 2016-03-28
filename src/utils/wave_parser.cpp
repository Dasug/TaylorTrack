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
* @brief Implementation of for taylortrack::utils::WaveParser class.
*/

#include "wave_parser.h"
#include <string>
#include <cstring>

namespace taylortrack {
namespace utils {

WaveParser::WaveParser(const char *file_name) {
  this->file_ = new std::ifstream(file_name, std::ios::in | std::ios::binary);

  if (this->file_->fail())
    valid_ = false;
  else
    this->parse_file();
}

WaveParser::~WaveParser() {
  delete this->file_;
}

bool WaveParser::is_done() {
  return !valid_ || this->file_->eof() ||
      (static_cast<int64_t>(this->data_offset_) +
          this->data_size_ <= static_cast<int64_t>(this->file_->tellg()));
}

int64_t WaveParser::get_sample_num() const {
  return this->data_size_ / this->block_align_;
}

void WaveParser::parse_file() {
  bool valid = true;
  char four_byte_buffer[5] = "";
  uint32_t fmt_size = 0;

  // Read RIFF header indication
  this->file_->read(four_byte_buffer, 4*sizeof(char));
  if (strcmp(four_byte_buffer, "RIFF") == 0) {
    // skip chunk size
    this->file_->seekg(8, std::ios_base::beg);

    // read chunk format
    valid &= static_cast<bool>(this->file_->read(four_byte_buffer, 4));
    if (strcmp(four_byte_buffer, "WAVE") == 0) {
      // read subchunk id
      valid &= static_cast<bool>(this->file_->read(four_byte_buffer, 4));
      if (strcmp(four_byte_buffer, "fmt ") == 0) {
        fmt_size = static_cast<uint32_t>(
            this->file_->get() | (this->file_->get() << 8) |
                (this->file_->get() << 16) | (this->file_->get() << 24));

        this->audio_format_ = static_cast<uint16_t>(this->file_->get() |
            (this->file_->get() << 8));
        this->num_channels_ = static_cast<uint16_t>(this->file_->get() |
            (this->file_->get() << 8));
        this->sample_rate_ = static_cast<uint32_t>(
            this->file_->get() | (this->file_->get() << 8) |
                (this->file_->get() << 16) | (this->file_->get() << 24));
        this->byte_rate_ = static_cast<uint32_t>(
            this->file_->get() | (this->file_->get() << 8) |
                (this->file_->get() << 16) | (this->file_->get() << 24));
        this->block_align_ = static_cast<uint16_t>(this->file_->get() |
            (this->file_->get() << 8));
        this->bits_per_sample_ = static_cast<uint16_t>(this->file_->get() |
            (this->file_->get() << 8));

        // read data header
        this->file_->seekg(20 + fmt_size, std::ios_base::beg);
        valid &= static_cast<bool>(this->file_->read(four_byte_buffer, 4));

        if (strcmp(four_byte_buffer, "data") == 0) {
          // read data subchunk length in bytes
          this->data_size_ = static_cast<uint32_t>(
              this->file_->get() | (this->file_->get() << 8) |
                  (this->file_->get() << 16) | (this->file_->get() << 24));
          this->data_offset_ = this->file_->tellg();
        } else {
          valid = false;
        }
      } else {
        valid = false;
      }
    } else {
      valid = false;
    }
  } else {
    valid = false;
  }
  this->valid_ = valid;
}

std::string WaveParser::get_samples(int64_t sample_num) {
  int64_t transfered_sample_size =
      ((this->block_align_ * sample_num) <= this->data_size_ ?
       this->block_align_ * sample_num :
       this->data_size_);
  std::string samples;
  for (unsigned int i = 0; i < transfered_sample_size; ++i) {
    samples.push_back(static_cast<char>(this->file_->get()));
  }
  return samples;
}

int WaveParser::get_bits_per_sample() const {
  return static_cast<int>(bits_per_sample_);
}

int WaveParser::get_block_align() const {
  return static_cast<int>(block_align_);
}

int64_t WaveParser::get_byte_rate() const {
  return static_cast<int64_t>(byte_rate_);
}

int64_t WaveParser::get_sample_rate() const {
  return static_cast<int64_t>(sample_rate_);
}

int WaveParser::get_num_channels() const {
  return static_cast<int>(num_channels_);
}

int WaveParser::get_audio_format() const {
  return static_cast<int>(audio_format_);
}

bool WaveParser::is_valid() const {
  return valid_;
}

}  // namespace utils
}  // namespace taylortrack
