#include <gtest/gtest.h>
#include "../utils/vad_simple.h"

TEST(VadSimpleTest, SimpleDetectionTestPositive) {
  taylortrack::utils::VadSimple test_vad = taylortrack::utils::VadSimple(0);
  double sample_data[] = {0.0, -0.055, 0, 0.055, 9.8282, 8121.0, 99999999.0, 9, 0};
  taylortrack::utils::RArray data(sample_data, 9);
  ASSERT_TRUE(test_vad.detect(data));

}

TEST(VadSimpleTest, SimpleDetectionTestPositive2) {
  taylortrack::utils::VadSimple TestVad = taylortrack::utils::VadSimple(0.25);
  double sample_data[] = {0.0, 0, 1, 0};
  taylortrack::utils::RArray data(sample_data, 4);
  ASSERT_TRUE(TestVad.detect(data));
}

TEST(VadSimpleTest, SimpleDetectionTestNegative) {
  taylortrack::utils::VadSimple TestVad = taylortrack::utils::VadSimple(1);
  double sample_data[] = {0.0, 0, 0, 0};
  taylortrack::utils::RArray data(sample_data, 4);
  ASSERT_FALSE(TestVad.detect(data));
}

TEST(VadSimpleTest, SimpleDetectionTestError) {
  taylortrack::utils::VadSimple TestVad = taylortrack::utils::VadSimple(1);
  double sample_data[] = {};
  taylortrack::utils::RArray data(sample_data, 1);
  ASSERT_FALSE(TestVad.detect(data));
}

TEST(VadSimpleTest, SimpleDetectionTestError2) {
  taylortrack::utils::VadSimple TestVad = taylortrack::utils::VadSimple(1);
  double sample_data[] = {9, 8};
  taylortrack::utils::RArray data(sample_data, 0);
  ASSERT_FALSE(TestVad.detect(data));
}