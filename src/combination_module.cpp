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
 * @brief Module to combine the results of the vision and speacker tracker.
 */
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <string>
#include <localization/vision_tracker.h>
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
      taylortrack::utils::parameter_parser::parse_streamer(argc, argv);
  if (!parameters.valid) {
    std::cout << "Invalid parameter usage. Please check --help" << std::endl;
    return EXIT_FAILURE;
  }
  taylortrack::utils::ConfigParser config(parameters.config);
  taylortrack::utils::CommunicationSettings out;
  std::vector<taylortrack::utils::CommunicationSettings> in;
  in = config.get_combination_communication_inports();
  out = config.get_combination_communication_out();

  // audio port
  yarp::os::BufferedPort<yarp::os::Bottle> buffered_port_audio_in;
  buffered_port_audio_in.open(in[0].port);
  // video port
  yarp::os::BufferedPort<yarp::os::Bottle> buffered_port_video_in;
  buffered_port_video_in.open(in[1].port);

  std::vector<double> weight = config.get_combination_configuration().weight;

  yarp::os::BufferedPort<yarp::os::Bottle> outport;
  outport.open(out.port);
  std::string inport = config.get_visualizer_communication_in().port;
  yarp.connect(outport.getName(), yarp::os::ConstString(inport));

  yarp::os::Bottle *audio = nullptr;
  yarp::os::Bottle *video = nullptr;
  int clear_audio = 0, clear_video = 0;

  while (true) {
    yarp::os::Bottle *audio_in = buffered_port_audio_in.read(false);
    yarp::os::Bottle *video_in = buffered_port_video_in.read(false);

    if (audio_in || video_in) {
      yarp::os::Bottle &bottle = outport.prepare();
      bottle.clear();
      if (audio_in) {
        audio = audio_in;
        clear_audio = 0;
      }
      if (video_in) {
        video = video_in;
        clear_video = 0;
      }

      if (audio && video) {
        for (int i = 0; i < audio->size(); ++i)
          bottle.addDouble((audio->get(i).asDouble() * weight[0]) + (video->get(i).asDouble() * weight[1]));
      } else if (audio) {
        for (int i = 0; i < audio->size(); ++i)
          bottle.addDouble(audio->get(i).asDouble());
      } else {
        for (int i = 0; i < video->size(); ++i)
          bottle.addDouble(video->get(i).asDouble());
      }
      ++clear_video;
      ++clear_audio;

      if (clear_audio == 10) {
        clear_audio = 0;
        audio = nullptr;
      }

      if (clear_video == 10) {
        clear_video = 0;
        video = nullptr;
      }
      outport.write(true);
    }  // End while
  }
}
