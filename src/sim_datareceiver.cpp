/**
 * @file
 * @brief Simulation for receiving data
 */

#include <yarp/os/all.h>
#include "utils/config_parser.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <yarp/sig/Matrix.h>

/**
 * @brief receiving data main method
 *
 * Initialize and open a port, wait for input from input bottle, and print positive message if successful
 */
int main(int argc, char *argv[]) {
    yarp::os::Network yarp;
    taylortrack::utils::ConfigParser config = taylortrack::utils::ConfigParser("../Testdata/real_config.conf");
    taylortrack::utils::CommunicationSettings in, out;
    in = config.get_video_communication_in();
    out = config.get_video_communication_out();
    yarp::os::BufferedPort<yarp::os::Bottle> *buffered_port_  = new yarp::os::BufferedPort<yarp::os::Bottle>();
    buffered_port_->open(in.port);
    taylortrack::utils::VideoSettings vs = config.get_video_configuration();
    /*taylortrack::localization::SrpPhat algorithm;// = taylortrack::localization::SrpPhat(audio.sample_rate, audio.mic_x, audio.mic_y, audio.grid_x, audio.grid_y, audio.interval, (int) audio.frame_size, audio.beta);
    algorithm.setParams(audio);*/
    /* visualizer
    yarp::os::BufferedPort<yarp::os::Bottle> outport;
    outport.open(out.port);
    yarp.connect(outport.getName(),yarp::os::ConstString(config.get_visualizer_communication_in().port));
    */
    while (true) {
        yarp::sig::Matrix yarp_frame;
        yarp::os::Bottle *input = buffered_port_->read(true);
        /* non blocking
        if(!input)
            continue;
         */
        input->pop().asList()->write(yarp_frame);
        cv::Mat frame = cv::Mat(yarp_frame.rows(), yarp_frame.cols(),16);
        for(int i = 0; i < yarp_frame.rows(); i++)
            for(int j = 0; j < yarp_frame.cols(); j++) {
                uint32_t pixel = (uint32_t) yarp_frame[i][j];
                cv::Vec3b pix;
                pix.val[2] = (uchar) (pixel & 0xFF);
                pixel >>= 8;
                pix.val[1] = (uchar) (pixel & 0xFF);
                pixel >>= 8;
                pix.val[0] = (uchar) (pixel & 0xFF);
                frame.at<cv::Vec3b>(i, j) = pix;
            }

        if(cv::waitKey(10) >= 0)
            break;
        cv::imshow("Recived frame", frame);

        /* visualizer
        yarp::os::Bottle& bottle = outport.prepare();
        bottle.clear();

        std::cout << "Send data: " << result[0] << " " << result[1] << std::endl;
        for (int k = 0; k < result.size(); ++k) {
            bottle.addDouble(result[k]);
        }

        outport.write(true);
         */
    }
    return 0;
}
