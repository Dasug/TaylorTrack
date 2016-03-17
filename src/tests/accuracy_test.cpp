//
// Created by Jannis Hoppe on 17.03.16.
//
#include "../input/wave_input_strategy.h"
#include "../utils/config_parser.h"
#include "../utils/fft_strategy.h"
#include "../localization/srpphat.h"
#include "../utils/vad_simple.h"


int main (){
  std::vector<int> predictions;
  int correct_degree = 180;
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
  taylortrack::localization::SrpPhat srp;
  srp.setConfig(config);
  params.file = "../Testdata/2_2.wav";
  params.inport = "abc";
  params.outport = "def";
  params.size = 2049;
  params.valid = true;
  int mics = 4;
  taylortrack::utils::VadSimple TestVad = taylortrack::utils::VadSimple(0.007);
  taylortrack::input::WaveInputStrategy strategy;
  strategy.set_parameters(params);
  strategy.set_config(config);
  while(!strategy.is_done()){
    std::vector<taylortrack::utils::RArray> signals;
    for (int i = 0; i < mics; ++i) {
      yarp::os::Bottle bottle;
      strategy.read(bottle);
      taylortrack::utils::RArray volume(params.size);
      int c = 0;
      for (int j = i; j < params.size; j += mics) {
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
  double acc = corrects / predictions.size();
  std::cout<<acc<<std::endl;
  return 0;
}