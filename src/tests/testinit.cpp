#include <stdlib.h>
#include <gtest/gtest.h>
#include "../utils/wave_parser.h"


int main(int argc, char **argv) {
    //taylortrack::utils::WaveParser parser = taylortrack::utils::WaveParser("../Testdata/Test.wav");
    //std::string samples = parser.get_samples(999999999999);
    //std::cout << samples << std::endl;
	testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


