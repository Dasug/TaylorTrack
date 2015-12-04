/*
 * simtest.cpp
 *
 *  Created on: 04.12.2015
 *      Author: tamarafriess
 */

#include "../input/dummy_input_strategy.h"
#include <gtest/gtest.h>

TEST(DummyTest, InitialNotDone) {
	taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
	EXPECT_FALSE(dummy.is_done());
}

TEST(DummyTest, Read) {
	taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
	EXPECT_EQ("Dummy Test successful", dummy.read());
}

TEST(DummyTest, ReadDone) {
	taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
	dummy.read();
	EXPECT_TRUE(dummy.is_done());
}
