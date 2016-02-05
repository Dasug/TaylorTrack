//
// Created by dasug on 05.02.16.
//

#include <string.h>
#include "wave_parser.h"


taylortrack::utils::WaveParser::WaveParser(const char *file_name) {
    this->file_ = new std::ifstream (file_name, std::ios::in|std::ios::binary);

    this->parse_file();
}


taylortrack::utils::WaveParser::~WaveParser() {
    delete this->file_;
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
        this->file_->read(four_byte_buffer, 4);
        if(strcmp(four_byte_buffer, "WAVE") == 0) {
            // read subchunk id
            this->file_->read(four_byte_buffer, 4);
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
                this->file_->read(four_byte_buffer, 4);

                if(strcmp(four_byte_buffer, "data") == 0) {
                    // read data subchunk length in bytes
                    this->data_size = this->file_->get() | (this->file_->get() << 8) | (this->file_->get() << 16) | (this->file_->get() << 24);
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


std::string taylortrack::utils::WaveParser::get_samples(int sample_num) {
    int transfered_sample_size = (int) ((this->block_align * sample_num) <= this->data_size ? this->block_align * sample_num : this->data_size);
    char samples[transfered_sample_size];
    for (int i = 0; i < (transfered_sample_size * this->block_align); ++i) {
        samples[i] = (char) this->file_->get();
    }
    return std::string(samples, transfered_sample_size);
}
