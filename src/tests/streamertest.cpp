
#include "../input/dummy_input_strategy.h"
#include "../sim/streamer.h"
#include <gtest/gtest.h>


TEST(StreamerTest, FailWhenDone) {
    taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
    taylortrack::sim::Streamer streamer = taylortrack::sim::Streamer(&dummy, "/test_out");
    dummy.read();
    EXPECT_FALSE(streamer.start_streaming("/test_in"));
}