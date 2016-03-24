/**
 * @file
 * @brief Simulation for receiving data
 */

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include "utils/config_parser.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "localization/vision_tracker.h"


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
#ifdef YARP_LITTLE_ENDIAN
  yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelBgra>>
      *buffered_port_ = new yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelBgra>>;
  yarp::sig::ImageOf<yarp::sig::PixelBgra> *input;
#else
  yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgba>> *buffered_port_ = new yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgba>>;
  yarp::sig::ImageOf<yarp::sig::PixelRgba> *input;
#endif
  //yarp::os::BufferedPort<yarp::os::Bottle> *buffered_port_  = new yarp::os::BufferedPort<yarp::os::Bottle>();
  buffered_port_->open(in.port);
  taylortrack::utils::VideoSettings vs = config.get_video_configuration();
  taylortrack::localization::VisionTracker algorithm;
  if (!algorithm.set_parameters(vs)) {
    std::cout << "Error: Classifier couln't be loaded!" << std::endl;
    return -1;
  }
  // visualizer
  yarp::os::BufferedPort<yarp::os::Bottle> outport;
  outport.open(out.port);
  yarp.connect(outport.getName(),yarp::os::ConstString(config.get_visualizer_communication_in().port));

  yarp.connect("/grabber", in.port);
  while (true) {
    input = buffered_port_->read(true);
    cv::Mat frame = cv::Mat(input->width(), input->height(), 24);

    for (int i = 0; i < input->width(); i++)
      for (int j = 0; j < input->height(); j++) {
        cv::Vec4b pixel = {input->safePixel(i,j).b, input->safePixel(i,j).g, input->safePixel(i,j).r, input->safePixel(i,j).a};
        frame.at<cv::Vec4b>(i, j) = pixel;
    }

    cv::transpose(frame, frame);
    cv::flip(frame, frame, 1);
    cv::cvtColor(frame, frame, cv::COLOR_BGRA2GRAY);
    cv::equalizeHist(frame, frame);
    algorithm.set_frame(frame);

    cv::waitKey(1);
    cv::imshow("Recived frame", frame);
    if(algorithm.detect_person()) {
      taylortrack::localization::RArray result = algorithm.get_position_distribution();

      yarp::os::Bottle &bottle = outport.prepare();
      bottle.clear();
      for (int i = 0; i < static_cast<int>(result.size()); ++i)
        bottle.addDouble(result[i]);

      outport.write(true);
    }
  }
  return 0;
}
