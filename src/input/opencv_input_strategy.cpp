
#include "opencv_input_strategy.h"

namespace taylortrack {
  namespace input {

    void OpenCVInputStrategy::set_parameters(taylortrack::utils::Parameters &params) {
      // Do nothing since this class doesn't need any of the parameters.
    }

    void OpenCVInputStrategy::set_config(taylortrack::utils::ConfigParser &config_parser) {
      frame_skip_ = config_parser.get_video_configuration().frame_skip;
      camera_id_ = config_parser.get_video_configuration().camera_id;
      video_capture_.open(camera_id_);
      if (!video_capture_.isOpened()) {
        std::cout << "Error opening the video capture!" << std::endl;
        done_ = true;
      }
    }

    yarp::os::Bottle OpenCVInputStrategy::read(yarp::os::Bottle &bottle) {
      while (video_capture_.read(frame_)) {
        if (frame_.empty()) {
          std::cout << "Error: No captured frame!" << std::endl;
          done_ = true;
          break;
        }
        cv::Mat gray_frame;
        cv::cvtColor(frame_, gray_frame, cv::COLOR_BGR2GRAY );
        cv::equalizeHist(gray_frame, gray_frame);
        cv::imshow(window_name_, gray_frame);
        if (frame_counter_ == 0) {
          yarp::sig::Matrix mat = yarp::sig::Matrix(gray_frame.rows, gray_frame.cols);
          for (int i = 0; i < gray_frame.rows; i++)
            for (int j = 0; j < gray_frame.cols; j++) {
              /*
              uint32_t pixel;
              pixel = frame_.at<cv::Vec3b>(i,j).val[0];
              pixel <<= 8;
              pixel = pixel | frame_.at<cv::Vec3b>(i,j).val[1];
              pixel <<= 8;
              pixel = pixel | frame_.at<cv::Vec3b>(i,j).val[2];
              mat[i][j] = pixel;*/
              mat[i][j] = gray_frame.at<int>(i,j);
            }
          std::cout << gray_frame.type() << std::endl;
          bottle.addList().read(mat);
          frame_counter_ = frame_skip_;
          if(cv::waitKey(10) >= 0)
            break;
          return bottle;
        }
        --frame_counter_;
      }
      return bottle;
    }

    bool OpenCVInputStrategy::is_done() {
      return done_;
    }
  }
}