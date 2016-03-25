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
 * @brief Simulation for receiving data
 */
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <string>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include "localization/vision_tracker.h"
#include "utils/config_parser.h"
#include "utils/parameter_parser.h"

/**
 * @brief opencv receiving data main method
 *
 * Initialize and open a port, wait for input from the opencv grabber, process the data and send it to the output port.
 */
int main(int argc,  const char *argv[]) {
  yarp::os::Network yarp;
  taylortrack::utils::Parameters parameters =
      taylortrack::utils::ParameterParser::parse_streamer(argc, argv);
  if (!parameters.valid) {
    std::cout << "Invalid parameter usage. Please check --help" << std::endl;
    return EXIT_FAILURE;
  }
  auto config = taylortrack::utils::ConfigParser(parameters.config);
  taylortrack::utils::CommunicationSettings in, out;
  in = config.get_video_communication_in();
  out = config.get_video_communication_out();
#ifdef YARP_LITTLE_ENDIAN
  auto *buffered_port_ =
      new yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelBgra>>;
  yarp::sig::ImageOf<yarp::sig::PixelBgra> *input;
#else
  auto *buffered_port_ =
      new yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgba>>;
  yarp::sig::ImageOf<yarp::sig::PixelRgba> *input;
#endif
  buffered_port_->open(in.port);
  taylortrack::utils::VideoSettings vs = config.get_video_configuration();
  taylortrack::localization::VisionTracker algorithm;
  if (!algorithm.set_parameters(vs)) {
    std::cout << "Error: Classifier couln't be loaded!" << std::endl;
    return -1;
  }

  yarp::os::BufferedPort<yarp::os::Bottle> outport;
  outport.open(out.port);
  std::string inport = config.get_visualizer_communication_in().port;
  yarp.connect(outport.getName(), yarp::os::ConstString(inport));
  yarp.connect("/grabber", in.port);

  while (true) {
    input = buffered_port_->read(true);
    cv::Mat frame = cv::Mat(input->width(), input->height(), 24);

    for (int i = 0; i < input->width(); i++)
      for (int j = 0; j < input->height(); j++) {
        cv::Vec4b pixel = {input->safePixel(i, j).b,
                           input->safePixel(i, j).g,
                           input->safePixel(i, j).r,
                           input->safePixel(i, j).a};
        frame.at<cv::Vec4b>(i, j) = pixel;
    }

    cv::transpose(frame, frame);
    cv::flip(frame, frame, 1);
    cv::cvtColor(frame, frame, cv::COLOR_BGRA2GRAY);
    cv::equalizeHist(frame, frame);
    algorithm.set_frame(frame);

    if (algorithm.detect_person()) {
      taylortrack::localization::RArray result =
          algorithm.get_position_distribution();

      yarp::os::Bottle &bottle = outport.prepare();
      bottle.clear();

      for (int i = 0; i < static_cast<int>(result.size()); ++i)
        bottle.addDouble(result[i]);
      outport.write(true);
    }  // End if
  }  // End while
}
