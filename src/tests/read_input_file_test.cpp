#include "gtest/gtest.h"
#include "zlib.h"
#include "../input/read_file_input_strategy.h"

TEST(InputFileTest, CRC32Match) {
  taylortrack::utils::Parameters params;
  params.file = "../Testdata/Test.txt";
  params.size = 0;
  taylortrack::input::ReadFileInputStrategy
      strategy = taylortrack::input::ReadFileInputStrategy(params);
  yarp::os::Bottle bottle;
  yarp::os::ConstString stringdata = strategy.read(bottle).pop().asString();
  const char *data = stringdata.c_str();
  bool done = strategy.is_done();

  std::cout << data << std::endl << std::endl;
  std::streampos size;
  std::ifstream file = std::ifstream("../Testdata/Test.txt", std::ios::in | std::ios::binary | std::ios::ate);
  if(file.is_open()) {
    size = file.tellg();
    file.close();
  }
  std::cout << data << std::endl << std::endl;
  unsigned long crc = crc32(0L, Z_NULL, 0);
  crc = crc32(crc, (const unsigned char *) data, size);
  std::cout << data << std::endl << std::endl;
  ASSERT_TRUE(done);
  ASSERT_EQ(crc, 0x1ed1ce7d);
}

TEST(InputFileTest, ReadTwoTimes) {
  taylortrack::utils::Parameters params;
  params.file = "../Testdata/Test.txt";
  params.size = 0;
  taylortrack::input::ReadFileInputStrategy
      strategy = taylortrack::input::ReadFileInputStrategy(params);
  yarp::os::Bottle bottle;
  const char *data = strategy.read(bottle).pop().asString().c_str();
  ASSERT_TRUE(strategy.is_done());
  bottle.clear();
  data = strategy.read(bottle).pop().asString().c_str();

  unsigned long crc = crc32(0L, Z_NULL, 0);
  crc = crc32(crc, (const unsigned char *) data, 0);

  ASSERT_EQ(0x00000000, crc);
  ASSERT_TRUE(strategy.is_done());
}

TEST(InputFileTest, NoFile) {
  taylortrack::utils::Parameters params;
  params.file = "nodata";
  params.size = 0;
  taylortrack::input::ReadFileInputStrategy strategy = taylortrack::input::ReadFileInputStrategy(params);

  yarp::os::Bottle bottle;

  ASSERT_STREQ("", strategy.read(bottle).pop().asString().c_str());
  ASSERT_TRUE(strategy.is_done());
}

TEST(InputFileTest, CRC32VideoTest) {
  taylortrack::utils::Parameters params;
  params.file = "../Testdata/Test.mp4";
  params.size = 0;
  taylortrack::input::ReadFileInputStrategy
      strategy = taylortrack::input::ReadFileInputStrategy(params);
  yarp::os::Bottle bottle;
  yarp::os::Bottle result = strategy.read(bottle);
  yarp::os::ConstString dataString = result.get(0).asString();
  const char *data = dataString.c_str();

  std::streampos size_;
  std::ifstream file_ = std::ifstream("../Testdata/Test.mp4", std::ios::in | std::ios::binary | std::ios::ate);
  if (file_.is_open()) {
    size_ = file_.tellg();
    file_.close();
  }

  unsigned long crc = crc32(0L, Z_NULL, 0);
  crc = crc32(crc, (const unsigned char *) data, size_);

  ASSERT_TRUE(strategy.is_done());
  ASSERT_EQ(crc, 0xe7c1d385);
}

TEST(InputFileTest, CRC32AudioTest) {
  taylortrack::utils::Parameters params;
  params.file = "../Testdata/Test.wav";
  params.size = 0;
  taylortrack::input::ReadFileInputStrategy
      strategy = taylortrack::input::ReadFileInputStrategy(params);
  yarp::os::Bottle bottle;
  yarp::os::Bottle result = strategy.read(bottle);
  yarp::os::ConstString dataString = result.get(0).asString();
  const char *data = dataString.c_str();

  std::streampos size_;
  std::ifstream file_ = std::ifstream("../Testdata/Test.wav", std::ios::in | std::ios::binary | std::ios::ate);
  if (file_.is_open()) {
    size_ = file_.tellg();
    file_.close();
  }

  unsigned long crc = crc32(0L, Z_NULL, 0);
  crc = crc32(crc, (const unsigned char *) data, size_);

  ASSERT_TRUE(strategy.is_done());
  ASSERT_EQ(crc, 0x22e40972);
}

TEST(InputFileTest, SizeUnequalZeroTest) {
  taylortrack::utils::Parameters params;
  params.file = "../Testdata/Test.txt";
  params.size = 5;
  taylortrack::input::ReadFileInputStrategy
      strategy = taylortrack::input::ReadFileInputStrategy(params);
  yarp::os::Bottle bottle;
  const char *data = strategy.read(bottle).pop().asString().c_str();
  bool done = strategy.is_done();

  ASSERT_STREQ("Lorem",data);
  ASSERT_FALSE(done);
  ASSERT_EQ(5, strlen(data));

  data = strategy.read(bottle).pop().asString().c_str();
  done = strategy.is_done();
  ASSERT_STREQ(" ipsu",data);
  ASSERT_FALSE(done);
  ASSERT_EQ(5, strlen(data));
}