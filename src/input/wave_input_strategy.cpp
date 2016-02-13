/**
* @file
* @brief Implementation of taylortrack::input::WaveInputStrategy class.
* @version 1
*/

#include <fstream>
#include <iostream>
#include "wave_input_strategy.h"

taylortrack::input::WaveInputStrategy::WaveInputStrategy(taylortrack::utils::Parameters& params) {
    this->parameter_ = params;
    this->waveParser = new taylortrack::utils::WaveParser(params.file);
}

bool taylortrack::input::WaveInputStrategy::is_done() {
    return waveParser->is_done();
}

taylortrack::input::WaveInputStrategy::~WaveInputStrategy() {
    delete this->waveParser;
}

yarp::os::Bottle taylortrack::input::WaveInputStrategy::read(yarp::os::Bottle& bottle) {

    if (waveParser->is_valid() && !waveParser->is_done()) {
        unsigned int sample_amount;
        if(parameter_.size <= 0) {
            sample_amount = waveParser->get_sample_num();
        } else {
            sample_amount = parameter_.size;
        }
        std::string samples = waveParser->get_samples(sample_amount);
        long sampleNum = samples.size() / (waveParser->get_bits_per_sample() / 8);
        long sampleSize = waveParser->get_block_align() / waveParser->get_num_channels();

        // Convert to Floats, change endian
        for (int i = 0; i < sampleNum; ++i) {
            long long temp = 0;
            for (int j = waveParser->get_bits_per_sample() - 8; j >= 0; j-= 8) {
                long samplePosition = i*sampleSize + (j / 8);
                long long sample = samples[samplePosition];
                long long shift_distance = j;
                temp |= (sample << shift_distance);
            }
            float cfloat = (float) temp / 32767.0f;
            bottle.addDouble((double) cfloat);
        }
    }

    return bottle;
}
