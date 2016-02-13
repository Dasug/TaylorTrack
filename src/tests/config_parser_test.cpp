#include <gtest/gtest.h>
#include "../utils/config_parser.h"

TEST(ConfigParserTest, ValidParsing) {
  taylortrack::utils::ConfigParser parser = taylortrack::utils::ConfigParser("../Testdata/taylortrack.conf");
  taylortrack::utils::GeneralOptions general = parser.get_general_configuration();
  taylortrack::utils::AudioSettings audio = parser.get_audio_configuration();
  taylortrack::utils::VideoSettings video = parser.get_video_configuration();
  taylortrack::utils::CombinationSettings combination = parser.get_combination_configuration();

  std::valarray<double> mic_x = {4, 8.2, 2, 9.123, 0, 3, 5, 5.123};
  std::valarray<double> mic_y = {0.1, 0.12, 0.123, 0.1245, 1234.1, 1234.128, 52, 6123.41234};
  bool mic_x_eq = false, mic_y_eq = false;

  for (unsigned int i = 0; i < audio.mic_x.size(); ++i) {
    mic_x_eq = mic_x[i] == audio.mic_x[i];
    if (!mic_x_eq)
      break;
  }

  for (unsigned int i = 0; i < audio.mic_x.size(); ++i) {
    mic_y_eq = mic_y[i] == audio.mic_y[i];
    if (!mic_y_eq)
      break;
  }

  ASSERT_TRUE(parser.is_valid());
  ASSERT_FALSE(general.console_output);

  ASSERT_STREQ("/test_audio_inport", audio.inport.c_str());
  ASSERT_STREQ("/test_audio_outport", audio.outport.c_str());
  ASSERT_EQ(53242342, audio.sample_rate);
  ASSERT_TRUE(mic_x_eq);
  ASSERT_TRUE(mic_y_eq);
  ASSERT_EQ(3.1472637, audio.beta);
  ASSERT_EQ(12, audio.grid_x);
  ASSERT_EQ(12, audio.grid_y);
  ASSERT_EQ(0.98765543123, audio.interval);
  ASSERT_EQ(8765, audio.frame_size);

  ASSERT_STREQ("/test_video_inport", video.inport.c_str());
  ASSERT_STREQ("/test_video_outport", video.outport.c_str());

  ASSERT_STREQ("/test_combination_inport", combination.inport.c_str());
  ASSERT_STREQ("/test_combination_outport", combination.outport.c_str());
}

TEST(ConfigParserTest, InvalidParsing) {
  taylortrack::utils::ConfigParser parser = taylortrack::utils::ConfigParser("../Testdata/taylortrack2.conf");
  ASSERT_FALSE(parser.is_valid());
}