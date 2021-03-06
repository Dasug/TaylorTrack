#include <gtest/gtest.h>
#include "input/dummy_input_strategy.h"
#include "sim/streamer.h"


TEST(StreamerTest, FailWhenDone) {
  taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
  taylortrack::sim::Streamer streamer(&dummy, "/test_out");
  yarp::os::Bottle bottle;
  dummy.read(&bottle);
  EXPECT_FALSE(streamer.start_streaming("/test_in"));
}
