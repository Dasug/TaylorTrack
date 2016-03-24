
#include "opencv_input_strategy.h"
#include <ctime>

namespace taylortrack {
  namespace input {

    void OpenCVInputStrategy::set_parameters(taylortrack::utils::Parameters &params) {
      // Do nothing since this class doesn't need any of the parameters.
    }

    void OpenCVInputStrategy::set_config(taylortrack::utils::ConfigParser &config_parser) {
      frame_skip_ = config_parser.get_video_configuration().frame_skip;
      camera_id_ = config_parser.get_video_configuration().camera_id;
      video_capture_.open(camera_id_);
      std::cout << video_capture_.get(cv::CAP_PROP_FPS) << std::endl;
      if (!video_capture_.isOpened()) {
        std::cout << "Error opening the video capture!" << std::endl;
        done_ = true;
      }
    }

    yarp::os::Bottle OpenCVInputStrategy::read(yarp::os::Bottle &bottle) {
      clock_t begin = clock();
      std::cout << video_capture_.get(cv::CAP_PROP_FPS) << std::endl;
      video_capture_.read(frame_);
      cv::imshow(window_name_, frame_);

      if (frame_.empty()) {
        std::cout << "Error: No captured frame!" << std::endl;
        done_ = true;
        return bottle;
      }


      cv::Mat gray_frame;
      cv::cvtColor(frame_, gray_frame, cv::COLOR_BGR2GRAY);
      cv::equalizeHist(gray_frame, gray_frame);
      yarp::sig::Matrix mat = yarp::sig::Matrix(gray_frame.rows, gray_frame.cols);

      for (int i = 0; i < gray_frame.rows; i++)
        for (int j = 0; j < gray_frame.cols; j++) {
          mat[i][j] = gray_frame.at<uchar>(i,j);
        }
      bottle.addList().read(mat);
      frame_counter_ = frame_skip_;
      cv::imshow(window_name_, gray_frame);
      cv::waitKey(1);
      clock_t end = clock();
      std::cout << "Relevanter frame: " << (double) (end-begin)/CLOCKS_PER_SEC << std::endl;
      return bottle;
    }

    bool OpenCVInputStrategy::is_done() {
      return done_;
    }
  }
}