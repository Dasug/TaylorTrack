/**
 * @file
 * @brief Simulation for receiving data
 */

#include "sim/data_receiver.h"
#include <yarp/os/all.h>
#include <utils/vad_simple.h>
#include "localization/srp_phat.h"
#include "utils/config_parser.h"
#include "utils/fft_strategy.h"

/**
 * @brief receiving data main method
 *
 * Initialize and open a port, wait for input from input bottle, and print positive message if successful
 */
int main(int argc, char *argv[]) {
    yarp::os::Network yarp;
    taylortrack::utils::ConfigParser config = taylortrack::utils::ConfigParser("../Testdata/real_config.conf");
    taylortrack::utils::CommunicationSettings out;
    out = config.get_audio_communication_out();
    taylortrack::sim::DataReceiver<yarp::os::Bottle> rec;
    bool data_receiver_initialized = rec.init(config.get_audio_communication_in());
    if(data_receiver_initialized) {
        taylortrack::utils::AudioSettings audio = config.get_audio_configuration();
        taylortrack::localization::SrpPhat algorithm;// = taylortrack::localization::SrpPhat(audio.sample_rate, audio.mic_x, audio.mic_y, audio.grid_x, audio.grid_y, audio.interval, (int) audio.frame_size, audio.beta);
        algorithm.set_config(config);
        int microphones = (int) audio.mic_x.size();
        yarp::os::BufferedPort<yarp::os::Bottle> outport;
        outport.open(out.port);
        yarp.connect(outport.getName(),yarp::os::ConstString(config.get_visualizer_communication_in().port));

        while (true) {
            std::vector<taylortrack::utils::RArray> signals;
            yarp::os::Bottle *new_data = rec.read_data(true);

            for (int i = 0; i < microphones; ++i) {
                taylortrack::utils::RArray volume(static_cast<size_t>(new_data->size()) / microphones);
                int c = 0;
                for (int j = i; j < new_data->size(); j += microphones) {
                    volume[c] = new_data->get(j).asDouble();
                    ++c;
                }
                signals.push_back(volume);
            }

            taylortrack::utils::VadSimple test_vad = taylortrack::utils::VadSimple(0.0000007);
            if(test_vad.detect(signals[0])) {
              algorithm.calculate_position_and_distribution(signals);

              taylortrack::utils::RArray result = algorithm.get_last_distribution();
              yarp::os::Bottle& bottle = outport.prepare();
              bottle.clear();

              for (int k = 0; k < static_cast<int>(result.size()); ++k) {
                bottle.addDouble(result[k]);
              }

              outport.write(true);
            } else {
              std::cout << "No voice activity detected." << std::endl;
            }
        }
    } else {
        std::cout << "Error initializing incoming communication..." << std::endl;
        return EXIT_FAILURE;
    }
}
