#include <gtest/gtest.h>
#include "../utils/parameters.h"
#include "../input/wave_input_strategy.h"

TEST(WaveInputTest, ValidExample) {
  taylortrack::utils::Parameters parameter;

  parameter.file = "../Testdata/Test.wav";
  // Read two samples at a time
  parameter.size = 2;

  taylortrack::input::WaveInputStrategy input;
  input.set_parameters(parameter);

  ASSERT_FALSE(input.is_done());

  // read first two samples
  yarp::os::Bottle bottle;
  input.read(bottle);

  ASSERT_EQ(2, bottle.size());

  ASSERT_FLOAT_EQ(-0.0011291848, bottle.get(0).asDouble());
  ASSERT_FLOAT_EQ(-0.0006408887, bottle.get(1).asDouble());
}

TEST(WaveInputTest, LargeExample) {
  taylortrack::utils::Parameters parameter;

  parameter.file = "../Testdata/Test.wav";
  // Read two samples at a time
  parameter.size = 999999999;

  taylortrack::input::WaveInputStrategy input;
  input.set_parameters(parameter);

  ASSERT_FALSE(input.is_done());

  // read first two samples
  yarp::os::Bottle bottle;
  input.read(bottle);

  ASSERT_EQ(90561, bottle.size());

  ASSERT_FLOAT_EQ(-0.0011291848, bottle.get(0).asDouble());
  ASSERT_FLOAT_EQ(-0.0006408887, bottle.get(1).asDouble());
  ASSERT_FLOAT_EQ(0.0028382214, bottle.get(90560).asDouble());
  ASSERT_TRUE(input.is_done());
}

TEST(WaveInputTest, NeverSetParameter) {

  taylortrack::input::WaveInputStrategy input;

  ASSERT_TRUE(input.is_done());

  // read hopefully empty bottle
  yarp::os::Bottle bottle;
  input.read(bottle);

  ASSERT_EQ(0, bottle.size());
}

TEST(WaveInputTest, InvalidFile) {
  taylortrack::utils::Parameters parameter;

  parameter.file = "../Testdata/Testnoriff.wav";
  // Read two samples at a time
  parameter.size = 2;

  taylortrack::input::WaveInputStrategy input;
  input.set_parameters(parameter);

  ASSERT_TRUE(input.is_done());

  // read hopefully empty bottle
  yarp::os::Bottle bottle;
  input.read(bottle);

  ASSERT_EQ(0, bottle.size());
}

TEST(WaveInputTest, NoSize) {
  taylortrack::utils::Parameters parameter;

  parameter.file = "../Testdata/Test.wav";
  // Read two samples at a time
  parameter.size = 0;

  taylortrack::input::WaveInputStrategy input;
  input.set_parameters(parameter);

  ASSERT_FALSE(input.is_done());

  // read first two samples
  yarp::os::Bottle bottle;
  input.read(bottle);

  ASSERT_EQ(90561, bottle.size());

  ASSERT_FLOAT_EQ(-0.0011291848, bottle.get(0).asDouble());
  ASSERT_FLOAT_EQ(-0.0006408887, bottle.get(1).asDouble());
  ASSERT_FLOAT_EQ(0.0028382214, bottle.get(90560).asDouble());
  ASSERT_TRUE(input.is_done());
}

TEST(WaveInputTest, SetConfig) {
  taylortrack::input::WaveInputStrategy input;

  taylortrack::utils::ConfigParser config;
  ASSERT_NO_FATAL_FAILURE(input.set_config(config));
}