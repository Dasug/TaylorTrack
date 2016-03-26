/**
 * @file
 * @brief Simulation for receiving data
 */

#include "sim/data_receiver.h"
#include <yarp/os/all.h>
#include "localization/srpphat.h"
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
    taylortrack::utils::CommunicationSettings in, out;
    in = config.get_audio_communication_in();
    out = config.get_audio_communication_out();
    taylortrack::sim::DataReceiver rec = taylortrack::sim::DataReceiver(in);
    taylortrack::utils::AudioSettings audio = config.get_audio_configuration();
    taylortrack::localization::SrpPhat algorithm;// = taylortrack::localization::SrpPhat(audio.sample_rate, audio.mic_x, audio.mic_y, audio.grid_x, audio.grid_y, audio.interval, (int) audio.frame_size, audio.beta);
    algorithm.set_config(config);
    int microphones = (int) audio.mic_x.size();
    yarp::os::BufferedPort<yarp::os::Bottle> outport;
    outport.open(out.port);
    yarp.connect(outport.getName(),yarp::os::ConstString(config.get_visualizer_communication_in().port));

    while (true) {
        std::vector<taylortrack::utils::RArray> signals;
        std::vector<double> new_data = rec.readData(true);
        std::cout << "Got data: " << new_data[0] << " " << new_data[1] << std::endl;
        for (int i = 0; i < microphones; ++i) {
            taylortrack::utils::RArray volume(new_data.size() / microphones);
            int c = 0;
            for (int j = i; j < static_cast<int>(new_data.size()); j += microphones) {
                volume[c] = new_data[j];
                ++c;
            }
            signals.push_back(volume);
        }
        
        taylortrack::utils::RArray result = algorithm.get_position_distribution(signals);

        yarp::os::Bottle& bottle = outport.prepare();
        bottle.clear();

        std::cout << "Send data: " << result[0] << " " << result[1] << std::endl;
        for (int k = 0; k < static_cast<int>(result.size()); ++k) {
            bottle.addDouble(result[k]);
        }

        outport.write(true);
    }
    return 0;
}
