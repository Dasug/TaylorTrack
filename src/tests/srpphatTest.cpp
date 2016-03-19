#include "gtest/gtest.h"
#include <math.h>
#include <fstream>
#include "localization/srpphat.h"
#include "utils/fft_lib.h"
#include "utils/config.h"

TEST(SrpPhatTest, imtdfTest) {
  taylortrack::utils::RArray point(2);
  taylortrack::utils::RArray point2(2);
  taylortrack::utils::RArray mic1(2);
  taylortrack::utils::RArray mic2(2);

  double mx[] = {0.055, 0.0, -0.055, 0.0};
  double my[] = {0.0, 0.055, 0.0, -0.055};
  taylortrack::utils::FftLib::RArray micsX(mx, 4);
  taylortrack::utils::FftLib::RArray micsY(my, 4);
  const int steps = 2048;
  taylortrack::localization::SrpPhat
      srp;
  taylortrack::utils::AudioSettings settings;
  settings.beta = 0.7;
  settings.sample_rate = 44100;
  settings.grid_x = 4.0;
  settings.grid_y = 4.0;
  settings.interval = 0.1;
  settings.mic_x = micsX;
  settings.mic_y = micsY;
  settings.frame_size = steps;
  taylortrack::utils::ConfigParser config;
  config.setAudioSettings(settings);

  srp.setConfig(config);
  point[0] = 0;
  point[1] = 339.42;
  mic1[0] = 1;
  mic1[1] = 0;
  mic2[0] = -1;
  mic2[1] = 0;

  double difference = srp.imtdf(point, mic1, mic2);
  ASSERT_EQ(0.0, difference);

  point2[0] = -2;
  point2[1] = 2;
  mic1[0] = -0.05;
  mic1[1] = 0;
  mic2[0] = 0.05;
  mic2[1] = 0;
  double difference2 = srp.imtdf(point2, mic1, mic2);
  ASSERT_TRUE(abs(difference2 - 0.0002077) < 0.000001);
}

TEST(SrpPhatTest, axisValueTest) {
  std::vector<taylortrack::utils::FftLib::RArray> vec;
  taylortrack::utils::RArray point(3);
  double mx[] = {0.0, -0.055, 0, 0.055};
  double my[] = {0.055, 0.0, -0.055, 0.0};
  taylortrack::utils::RArray micsX(mx, 4);
  taylortrack::utils::RArray micsY(my, 4);
  const int steps = 2048;
  taylortrack::localization::SrpPhat
      srp;
  taylortrack::utils::AudioSettings settings;
  settings.beta = 0.7;
  settings.sample_rate = 44100;
  settings.grid_x = 4.0;
  settings.grid_y = 4.0;
  settings.interval = 0.1;
  settings.mic_x = micsX;
  settings.mic_y = micsY;
  settings.frame_size = steps;

  taylortrack::utils::ConfigParser config;
  config.setAudioSettings(settings);

  srp.setConfig(config);

  std::vector<double> xax = srp.getAxisvalues(true);
  std::vector<double> yax = srp.getAxisvalues(false);

  ASSERT_EQ(41, xax.size());
  ASSERT_EQ(41, yax.size());
  ASSERT_DOUBLE_EQ(2.0, yax[0]);
  ASSERT_DOUBLE_EQ(-2.0, xax[0]);
  ASSERT_DOUBLE_EQ(2.0, xax[40]);
  ASSERT_DOUBLE_EQ(-2.0, yax[40]);
}

TEST(SrpPhatTest, gccTest) {
  taylortrack::utils::RArray mics(4);
  double mx[] = {0.055, 0.0, -0.055, 0.0};
  double my[] = {0.0, 0.055, 0.0, -0.055};
  taylortrack::utils::FftLib::RArray micsX(mx, 4);
  taylortrack::utils::FftLib::RArray micsY(my, 4);
  const int steps = 2048;
  taylortrack::localization::SrpPhat
      srp;
  taylortrack::utils::AudioSettings settings;
  settings.beta = 0.7;
  settings.sample_rate = 44100;
  settings.grid_x = 4.0;
  settings.grid_y = 4.0;
  settings.interval = 0.1;
  settings.mic_x = micsX;
  settings.mic_y = micsY;
  settings.frame_size = steps;

  taylortrack::utils::ConfigParser config;
  config.setAudioSettings(settings);

  srp.setConfig(config);

  taylortrack::utils::RArray sig1 = srp.getMicSignal("../Testdata/0-180_short.txt");
  taylortrack::utils::RArray sig2 = srp.getMicSignal("../Testdata/90-180_short.txt");

  taylortrack::utils::RArray temp1 = sig1[std::slice(0, 257, 1)];
  taylortrack::utils::RArray temp2 = sig2[std::slice(0, 256, 1)];

  taylortrack::utils::RArray gcca = srp.gcc(temp1, temp2);

  ASSERT_TRUE(abs(gcca.max() - 0.0529023) < 0.0001);
}

TEST(SrpPhatTest, pointToAngleTest) {
  int x = 1;
  int y = 1;
  int x2 = 0;
  int y2 = -1;
  int x3 = -1;
  int y3 = 0;
  double x4 = 1.4153;
  double y4 = 5.41;
  double x5 = 0;
  double y5 = 0;
  double mx[] = {0.055, 0.0, -0.055, 0.0};
  double my[] = {0.0, 0.055, 0.0, -0.055};
  taylortrack::utils::FftLib::RArray micsX(mx, 4);
  taylortrack::utils::FftLib::RArray micsY(my, 4);
  const int steps = 2048;
  taylortrack::localization::SrpPhat
      srp;
  taylortrack::utils::AudioSettings settings;
  settings.beta = 0.7;
  settings.sample_rate = 44100;
  settings.grid_x = 4.0;
  settings.grid_y = 4.0;
  settings.interval = 0.1;
  settings.mic_x = micsX;
  settings.mic_y = micsY;
  settings.frame_size = steps;

  taylortrack::utils::ConfigParser config;
  config.setAudioSettings(settings);

  srp.setConfig(config);
  int deg = srp.pointToDegree(x, y);
  int deg2 = srp.pointToDegree(x2, y2);
  int deg3 = srp.pointToDegree(x3, y3);
  int deg4 = srp.pointToDegree(x4, y4);
  int deg5 = srp.pointToDegree(x4, -y4);
  int deg6 = srp.pointToDegree(x5, y5);
  ASSERT_EQ(45, deg);
  ASSERT_EQ(270, deg2);
  ASSERT_EQ(180, deg3);
  ASSERT_EQ(75, deg4);
  ASSERT_EQ(285, deg5);
  ASSERT_EQ(0, deg6);

}

TEST(SrpPhatTest, getDelayTensorTest) {
  double mx[] = {0.0, -0.055, 0, 0.055};
  double my[] = {0.055, 0.0, -0.055, 0.0};
  taylortrack::utils::RArray micsX(mx, 4);
  taylortrack::utils::RArray micsY(my, 4);

  taylortrack::localization::SrpPhat
      srp;
  taylortrack::utils::AudioSettings settings;
  settings.beta = 0.7;
  settings.sample_rate = 44100;
  settings.grid_x = 4.0;
  settings.grid_y = 4.0;
  settings.interval = 0.1;
  settings.mic_x = micsX;
  settings.mic_y = micsY;
  settings.frame_size = 2048;

  taylortrack::utils::ConfigParser config;
  config.setAudioSettings(settings);

  srp.setConfig(config);

  std::vector<std::vector<std::vector<double>>> difference;

  difference = srp.get_delay_tensor();
  ASSERT_EQ(0, difference[0][0][0]);
  ASSERT_TRUE(difference[0][28][1] - 0.0001199 < 0.000001);
  ASSERT_EQ(0, difference[40][0][2]);
}

TEST(SrpPhatTest, getMicPairsTest) {
  taylortrack::utils::RArray mics(4);

  taylortrack::localization::SrpPhat srp;

  taylortrack::utils::AudioSettings settings;
  settings.beta = 0.7;
  settings.sample_rate = 44100;
  settings.grid_x = 4.0;
  settings.grid_y = 4.0;
  settings.interval = 0.1;
  settings.mic_x = mics;
  settings.mic_y = mics;
  settings.frame_size = 2048;

  taylortrack::utils::ConfigParser config;
  config.setAudioSettings(settings);

  srp.setConfig(config);

  std::vector<std::tuple<int, int>> micP = srp.getMicPairs();

  ASSERT_EQ(0, std::get<0>(micP[0]));
  ASSERT_EQ(1, std::get<1>(micP[0]));
  ASSERT_EQ(0, std::get<0>(micP[1]));
  ASSERT_EQ(2, std::get<1>(micP[1]));
  ASSERT_EQ(0, std::get<0>(micP[2]));
  ASSERT_EQ(3, std::get<1>(micP[2]));
  ASSERT_EQ(1, std::get<0>(micP[3]));
  ASSERT_EQ(2, std::get<1>(micP[3]));
  ASSERT_EQ(1, std::get<0>(micP[4]));
  ASSERT_EQ(3, std::get<1>(micP[4]));
  ASSERT_EQ(2, std::get<0>(micP[5]));
  ASSERT_EQ(3, std::get<1>(micP[5]));

}

TEST(SrpPhatTest, gccGridTest) {
  double mx[] = {0.0, -0.055, 0, 0.055};
  double my[] = {0.055, 0.0, -0.055, 0.0};
  double beta = 0.7;
  taylortrack::utils::RArray micsX(mx, 4);
  taylortrack::utils::RArray micsY(my, 4);
  taylortrack::localization::SrpPhat
      srp;
  taylortrack::utils::AudioSettings settings;
  settings.beta = 0.7;
  settings.sample_rate = 44100;
  settings.grid_x = 4.0;
  settings.grid_y = 4.0;
  settings.interval = 0.1;
  settings.mic_x = micsX;
  settings.mic_y = micsY;
  settings.frame_size = 2048;

  taylortrack::utils::ConfigParser config;
  config.setAudioSettings(settings);

  srp.setConfig(config);

  taylortrack::utils::RArray sig1 = srp.getMicSignal("../Testdata/0-180_short.txt");
  taylortrack::utils::RArray sig2 = srp.getMicSignal("../Testdata/90-180_short.txt");
  taylortrack::utils::RArray sig3 = srp.getMicSignal("../Testdata/180-180_short.txt");
  taylortrack::utils::RArray sig4 = srp.getMicSignal("../Testdata/270-180_short.txt");

  std::vector<taylortrack::utils::RArray> signals;
  signals.push_back(sig1);
  signals.push_back(sig2);
  signals.push_back(sig3);
  signals.push_back(sig4);
  std::vector<std::vector<double>> gcca = srp.getGccGrid(signals);
  ASSERT_TRUE(gcca[0][0] - 0.1636087 < 0.000001);
  ASSERT_TRUE(gcca[18][0] - 0.14998061 < 0.000001);
}

TEST(SrpPhatTest, getPositionTest) {
  double mx[] = {0.055, 0.0, -0.055, 0.0};
  double my[] = {0.0, 0.055, 0.0, -0.055};
  taylortrack::utils::FftLib::RArray micsX(mx, 4);
  taylortrack::utils::FftLib::RArray micsY(my, 4);
  const int steps = 2048;
  taylortrack::localization::SrpPhat
      srp;
  taylortrack::utils::AudioSettings settings;
  settings.beta = 0.7;
  settings.sample_rate = 44100;
  settings.grid_x = 4.0;
  settings.grid_y = 4.0;
  settings.interval = 0.1;
  settings.mic_x = micsX;
  settings.mic_y = micsY;
  settings.frame_size = steps;

  taylortrack::utils::ConfigParser config;
  config.setAudioSettings(settings);

  srp.setConfig(config);

  taylortrack::utils::FftLib::RArray sig1 = srp.getMicSignal("../Testdata/0-180_short.txt");
  taylortrack::utils::FftLib::RArray sig2 = srp.getMicSignal("../Testdata/90-180_short.txt");
  taylortrack::utils::FftLib::RArray sig3 = srp.getMicSignal("../Testdata/180-180_short.txt");
  taylortrack::utils::FftLib::RArray sig4 = srp.getMicSignal("../Testdata/270-180_short.txt");
  taylortrack::utils::FftLib::RArray estimates(4);

  std::vector<taylortrack::utils::FftLib::RArray> signals;
  signals.push_back(sig1);
  signals.push_back(sig2);
  signals.push_back(sig3);
  signals.push_back(sig4);
  int signalLength = signals[0].size();
  int sigsteps = signalLength / steps + 1;
  for (int step = 1; step < sigsteps; step++) {
    std::vector<taylortrack::utils::FftLib::RArray> signals2;

    taylortrack::utils::FftLib::RArray signalSlice1 = sig1[std::slice((2049 - 1) * (step - 1), 2049, 1)];
    taylortrack::utils::FftLib::RArray signalSlice2 = sig2[std::slice((2049 - 1) * (step - 1), 2049, 1)];
    taylortrack::utils::FftLib::RArray signalSlice3 = sig3[std::slice((2049 - 1) * (step - 1), 2049, 1)];
    taylortrack::utils::FftLib::RArray signalSlice4 = sig4[std::slice((2049 - 1) * (step - 1), 2049, 1)];
    signals2.push_back(signalSlice1);
    signals2.push_back(signalSlice2);
    signals2.push_back(signalSlice3);
    signals2.push_back(signalSlice4);
    int pos = srp.getPosition(signals2);
    estimates[step] = pos;
  }
  ASSERT_EQ(180, estimates[1]);
  ASSERT_EQ(180, estimates[2]);
}

TEST(SrpPhatTest, getPositionDistributionTest) {
  double mx[] = {0.055, 0.0, -0.055, 0.0};
  double my[] = {0.0, 0.055, 0.0, -0.055};
  taylortrack::utils::FftLib::RArray micsX(mx, 4);
  taylortrack::utils::FftLib::RArray micsY(my, 4);
  const int steps = 2048;
  taylortrack::localization::SrpPhat
      srp;
  taylortrack::utils::AudioSettings settings;
  settings.beta = 0.7;
  settings.sample_rate = 44100;
  settings.grid_x = 4.0;
  settings.grid_y = 4.0;
  settings.interval = 0.1;
  settings.mic_x = micsX;
  settings.mic_y = micsY;
  settings.frame_size = steps;

  taylortrack::utils::ConfigParser config;
  config.setAudioSettings(settings);

  srp.setConfig(config);

  taylortrack::utils::FftLib::RArray sig1 = srp.getMicSignal("../Testdata/0-180_short.txt");
  taylortrack::utils::FftLib::RArray sig2 = srp.getMicSignal("../Testdata/90-180_short.txt");
  taylortrack::utils::FftLib::RArray sig3 = srp.getMicSignal("../Testdata/180-180_short.txt");
  taylortrack::utils::FftLib::RArray sig4 = srp.getMicSignal("../Testdata/270-180_short.txt");
  taylortrack::utils::FftLib::RArray estimates(4);
  std::vector<taylortrack::utils::FftLib::RArray> signals;
  signals.push_back(sig1);
  signals.push_back(sig2);
  signals.push_back(sig3);
  signals.push_back(sig4);
  int signalLength = signals[0].size();
  int sigsteps = signalLength / steps + 1;
  for (int step = 1; step < sigsteps; step++) {
    std::vector<taylortrack::utils::FftLib::RArray> signals2;

    taylortrack::utils::FftLib::RArray signalSlice1 = sig1[std::slice((2049 - 1) * (step - 1), 2049, 1)];
    taylortrack::utils::FftLib::RArray signalSlice2 = sig2[std::slice((2049 - 1) * (step - 1), 2049, 1)];
    taylortrack::utils::FftLib::RArray signalSlice3 = sig3[std::slice((2049 - 1) * (step - 1), 2049, 1)];
    taylortrack::utils::FftLib::RArray signalSlice4 = sig4[std::slice((2049 - 1) * (step - 1), 2049, 1)];
    signals2.push_back(signalSlice1);
    signals2.push_back(signalSlice2);
    signals2.push_back(signalSlice3);
    signals2.push_back(signalSlice4);
    taylortrack::utils::FftLib::RArray pos = srp.getPositionDistribution(signals2);
    int maxpos = srp.findVal(pos, pos.max());
    estimates[step] = maxpos;
  }
  ASSERT_EQ(180, estimates[1]);
  ASSERT_EQ(180, estimates[2]);
}