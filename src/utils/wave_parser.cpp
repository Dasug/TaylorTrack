/**
* @file
* @brief Implementation of for taylortrack::utils::WaveParser class.
* @version 1
*/

#include <string.h>
#include "wave_parser.h"


taylortrack::utils::WaveParser::WaveParser(const char *file_name) {
    this->file_ = new std::ifstream (file_name, std::ios::in|std::ios::binary);

    this->parse_file();
}


taylortrack::utils::WaveParser::~WaveParser() {
    delete this->file_;
}

bool taylortrack::utils::WaveParser::is_done() {
    return !valid || this->file_->eof() || ((unsigned long) this->data_offset + this->data_size <= (unsigned long) this->file_->tellg());
}

unsigned long taylortrack::utils::WaveParser::get_sample_num() {
    return this->data_size / this->block_align;
}



void taylortrack::utils::WaveParser::parse_file() {
    bool valid = true;
    char four_byte_buffer[4];
    unsigned long fmt_size = 0;

    // Read RIFF header indication
    this->file_->read(four_byte_buffer, 4);
    if(strcmp(four_byte_buffer, "RIFF") == 0) {
        // skip chunk size
        this->file_->seekg(8, std::ios_base::beg);

        // read chunk format
        valid &= (bool) this->file_->read(four_byte_buffer, 4);
        if(strcmp(four_byte_buffer, "WAVE") == 0) {
            // read subchunk id
            valid &= (bool) this->file_->read(four_byte_buffer, 4);
            if(strcmp(four_byte_buffer, "fmt ") == 0) {
                fmt_size = this->file_->get() | (this->file_->get() << 8) | (this->file_->get() << 16) | (this->file_->get() << 24);

                this->audio_format = (unsigned short) (this->file_->get() | (this->file_->get() << 8));
                this->num_channels = (unsigned short) (this->file_->get() | (this->file_->get() << 8));
                this->sample_rate = this->file_->get() | (this->file_->get() << 8) | (this->file_->get() << 16) | (this->file_->get() << 24);
                this->byte_rate = this->file_->get() | (this->file_->get() << 8) | (this->file_->get() << 16) | (this->file_->get() << 24);
                this->block_align = (unsigned short) (this->file_->get() | (this->file_->get() << 8));
                this->bits_per_sample = (unsigned short) (this->file_->get() | (this->file_->get() << 8));

                // read data header
                this->file_->seekg(20 + fmt_size, std::ios_base::beg);
                valid &= (bool) this->file_->read(four_byte_buffer, 4);

                if(strcmp(four_byte_buffer, "data") == 0) {
                    // read data subchunk length in bytes
                    this->data_size = this->file_->get() | (this->file_->get() << 8) | (this->file_->get() << 16) | (this->file_->get() << 24);
                    this->data_offset = this->file_->tellg();
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

    this->valid = valid;

}


std::string taylortrack::utils::WaveParser::get_samples(unsigned int sample_num) {
    unsigned long transfered_sample_size = ((this->block_align * sample_num) <= this->data_size ? this->block_align * sample_num : this->data_size);
    char samples[transfered_sample_size];
    for (int i = 0; i < transfered_sample_size; ++i) {
        samples[i] = (char) this->file_->get();
    }
    return std::string(samples, transfered_sample_size);
}

unsigned short taylortrack::utils::WaveParser::get_bits_per_sample() const {
    return bits_per_sample;
}

unsigned short taylortrack::utils::WaveParser::get_block_align() const {
    return block_align;
}

unsigned long taylortrack::utils::WaveParser::get_byte_rate() const {
    return byte_rate;
}

unsigned long taylortrack::utils::WaveParser::get_sample_rate() const {
    return sample_rate;
}

unsigned short taylortrack::utils::WaveParser::get_num_channels() const {
    return num_channels;
}

unsigned short taylortrack::utils::WaveParser::get_audio_format() const {
    return audio_format;
}

bool taylortrack::utils::WaveParser::is_valid() const {
    return valid;
}
