//
// Created by Jannis Hoppe on 17.03.16.
//
#include "../input/wave_input_strategy.h"
#include "../utils/config_parser.h"
#include "../utils/fft_strategy.h"
#include "../localization/srpphat.h"
#include "../utils/vad_simple.h"
#include "../utils/fft_lib.h"


int main (){
  std::vector<int> predictions;
  double mx[] = {0.055, 0.0, -0.055, 0.0};
  double my[] = {0.0, 0.055, 0.0, -0.055};
  taylortrack::utils::RArray micsX(mx, 4);
  taylortrack::utils::RArray micsY(my, 4);
  taylortrack::utils::AudioSettings settings;
  settings.beta = 0.7;
  settings.sample_rate = 44100;
  settings.grid_x = 4.0;
  settings.grid_y = 4.0;
  settings.interval = 0.1;
  settings.mic_x = micsX;
  settings.mic_y = micsY;
  settings.frame_size = 2048;
  taylortrack::utils::Parameters params;
  taylortrack::utils::ConfigParser config;
  config.setAudioSettings(settings);
  params.inport = "abc";
  params.outport = "def";
  params.size = 2049;
  params.valid = true;
  int mics = 4;
  taylortrack::utils::VadSimple TestVad = taylortrack::utils::VadSimple(0.000004);

  int total_predictions = 0;
  int correct_predictions = 0;

  std::string files[] = {"../Testdata/2_1.wav", "../Testdata/2_2.wav", "../Testdata/2_3ton.wav", "../Testdata/2_3log.wav", "../Testdata/2_4log.wav", "../Testdata/2_4ton.wav", "../Testdata/2_5ton.wav", "../Testdata/2_5log.wav", "../Testdata/2_6log.wav", "../Testdata/2_6ton.wav", "../Testdata/2_7ton.wav", "../Testdata/2_7log.wav", "../Testdata/2_8log.wav", "../Testdata/2_8ton.wav", "../Testdata/2_9ton.wav", "../Testdata/2_9log.wav"};
  int degrees[] = {180, 180, 45, 45, 135, 135, 270, 270, 315, 315, 225, 225, 270, 270, 315, 315};

  for (int cfile = 0; cfile < files->size(); cfile++) {
    taylortrack::input::WaveInputStrategy strategy;
    strategy.set_config(config);
    taylortrack::localization::SrpPhat srp;
    srp.setConfig(config);
    predictions.clear();
    int correct_degree = degrees[cfile];
    params.file = files[cfile].c_str();
    strategy.set_parameters(params);
    int count = 0;

    while(!strategy.is_done()){
      count++;
      std::vector<taylortrack::utils::RArray> signals;
      yarp::os::Bottle bottle;
      bottle.clear();
      strategy.read(bottle);
      for (int i = 0; i < mics; ++i) {
        taylortrack::utils::RArray volume(params.size);
        int c = 0;
        for (int j = i; j < params.size * 4; j += mics) {
          volume[c] = bottle.get(j).asDouble();
          ++c;
        }

        signals.push_back(volume);
      }

      if (TestVad.detect(signals[0]))
        predictions.push_back(srp.getPosition(signals));
    }
    int corrects = 0;
    for (int k=0;k<predictions.size();k++){
      if (std::abs(predictions[k]-correct_degree) <=3 ){
        corrects++;
      }
    }
    double acc = (double) corrects / (double) predictions.size();
    correct_predictions += corrects;
    total_predictions += predictions.size();
    std::cout<< params.file << ": count: " << count << " acc: " << acc << " pred: " << predictions.size() <<std::endl;

    double total_accuracy = static_cast<double>(correct_predictions) / static_cast<double>(total_predictions);
    std::cout << correct_predictions << "/" << total_predictions << ": " << total_accuracy << std::endl;
  }

  double total_accuracy = static_cast<double>(correct_predictions) / static_cast<double>(total_predictions);
  std::cout << correct_predictions << "/" << total_predictions << ": " << total_accuracy << std::endl;


  return 0;
}