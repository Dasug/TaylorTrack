#include <gtest/gtest.h>
#include "../utils/wave_parser.h"

TEST(WaveParserTest, ValidExample) {
  taylortrack::utils::WaveParser parser = taylortrack::utils::WaveParser("../Testdata/Test.wav");
  ASSERT_TRUE(parser.is_valid());
  ASSERT_EQ(parser.get_sample_rate(), 44100);
  ASSERT_EQ(parser.get_num_channels(), 1);
  ASSERT_EQ(parser.get_byte_rate(), 88200);
  ASSERT_EQ(parser.get_bits_per_sample(), 16);
  ASSERT_EQ(parser.get_audio_format(), 0x0001);
  ASSERT_EQ(parser.get_block_align(), 2);

  std::string samples = parser.get_samples(2);

  ASSERT_EQ(samples, std::string("\xdb\xff\xeb\xff"));

  // Calculate float representation
  int sample_value = (samples[1] << 8) | samples[0];
  float sample_float_value = (float) sample_value / 32767.0f;

  ASSERT_FLOAT_EQ(-0.0011291848f, sample_float_value);

  sample_value = (samples[3] << 8) | samples[2];
  sample_float_value = (float) sample_value / 32767.0f;

  ASSERT_FLOAT_EQ(-0.0006408887f, sample_float_value);
}

TEST(WaveParserTest, NoRIFFHeader) {
  taylortrack::utils::WaveParser parser = taylortrack::utils::WaveParser("../Testdata/Testnoriff.wav");
  ASSERT_FALSE(parser.is_valid());
}

TEST(WaveParserTest, NoDataHeader) {
  taylortrack::utils::WaveParser parser = taylortrack::utils::WaveParser("../Testdata/Testnodata.wav");
  ASSERT_FALSE(parser.is_valid());
}

TEST(WaveParserTest, NofmtHeader) {
  taylortrack::utils::WaveParser parser = taylortrack::utils::WaveParser("../Testdata/Testnofmt.wav");
  ASSERT_FALSE(parser.is_valid());
}

TEST(WaveParserTest, NoWaveFormat) {
  taylortrack::utils::WaveParser parser = taylortrack::utils::WaveParser("../Testdata/Testwave.wav");
  ASSERT_FALSE(parser.is_valid());
}