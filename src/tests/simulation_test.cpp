#include <gtest/gtest.h>
#include "input/dummy_input_strategy.h"

TEST(DummyTest, InitialNotDone) {
  taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
  EXPECT_FALSE(dummy.is_done());
}

TEST(DummyTest, Read) {
  taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
  yarp::os::Bottle bottle;
  ASSERT_STREQ("Dummy Test successful", dummy.read(&bottle).pop().asString().c_str());
}

TEST(DummyTest, ReadDone) {
  taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
  yarp::os::Bottle bottle;
  dummy.read(&bottle);
  EXPECT_TRUE(dummy.is_done());
}

TEST(StreamerTest, SetDummyParameters) {
  taylortrack::input::DummyInputStrategy dummy;
  taylortrack::utils::ConfigParser config;
  taylortrack::utils::Parameters params;
  ASSERT_NO_FATAL_FAILURE(dummy.set_parameters(params));
  ASSERT_NO_FATAL_FAILURE(dummy.set_config(config));
}
