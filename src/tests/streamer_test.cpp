#include <gtest/gtest.h>
#include "input/dummy_input_strategy.h"
#include "sim/streamer.h"


TEST(StreamerTest, FailWhenDone) {
  taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
  taylortrack::sim::Streamer streamer = taylortrack::sim::Streamer(&dummy, "/test_out");
  yarp::os::Bottle bottle;
  dummy.read(bottle);
  EXPECT_FALSE(streamer.start_streaming("/test_in"));
}

TEST(StreamerTest, SetDummyParameters) {
  taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
  taylortrack::utils::ConfigParser config;
  taylortrack::utils::Parameters params;
  ASSERT_NO_FATAL_FAILURE(dummy.set_parameters(params));
  ASSERT_NO_FATAL_FAILURE(dummy.set_config(config));
}