#include "../utils/parameter_parser.h"
#include "gtest/gtest.h"
#include "zlib.h"
#include "../input/read_file_input_strategy.h"

TEST(InputFileTest,CRC32Match) {
  taylortrack::input::ReadFileInputStrategy strategy = taylortrack::input::ReadFileInputStrategy("../Testdata/Test.txt");
  const char *data = strategy.read();

  std::streampos size_;
  std::ifstream file_ = std::ifstream ("../Testdata/Test.txt", std::ios::in|std::ios::binary|std::ios::ate);
  if(file_.is_open()) {
    size_ = file_.tellg();
    file_.close();
  }

  unsigned long  crc = crc32(0L, Z_NULL, 0);
  crc = crc32(crc, (const unsigned char*) data,size_);

  ASSERT_EQ(true,strategy.is_done());
  ASSERT_EQ(crc,0x1ed1ce7d);
}

TEST(InputFileTest,ReadTwoTimes) {
  taylortrack::input::ReadFileInputStrategy strategy = taylortrack::input::ReadFileInputStrategy("../Testdata/Test.txt");
  const char *data = strategy.read();
  ASSERT_EQ(true, strategy.is_done());
  data = strategy.read();

  std::streampos size_;
  std::ifstream file_ = std::ifstream ("../Testdata/Test.txt", std::ios::in|std::ios::binary|std::ios::ate);
  if(file_.is_open()) {
    size_ = file_.tellg();
    file_.close();
  }

  unsigned long  crc = crc32(0L, Z_NULL, 0);
  crc = crc32(crc, (const unsigned char*) data,size_);

  ASSERT_EQ(crc,0x1ed1ce7d);
  ASSERT_EQ(true, strategy.is_done());
}

TEST(InputFileTest,NoFile) {
  taylortrack::input::ReadFileInputStrategy *strategy = new taylortrack::input::ReadFileInputStrategy("nodata");

  ASSERT_EQ(NULL, strategy->read());
  ASSERT_EQ(true, strategy->is_done());
}

TEST(InputFileTest,CRC32VideoTest) {
  taylortrack::input::ReadFileInputStrategy strategy = taylortrack::input::ReadFileInputStrategy("../Testdata/Test.mp4");
  const char *data = strategy.read();

  std::streampos size_;
  std::ifstream file_ = std::ifstream ("../Testdata/Test.mp4", std::ios::in|std::ios::binary|std::ios::ate);
  if(file_.is_open()) {
    size_ = file_.tellg();
    file_.close();
  }

  unsigned long  crc = crc32(0L, Z_NULL, 0);
  crc = crc32(crc, (const unsigned char*) data,size_);

  ASSERT_EQ(true,strategy.is_done());
  ASSERT_EQ(crc,0xe7c1d385);
}

TEST(InputFileTest,CRC32AudioTest) {
  taylortrack::input::ReadFileInputStrategy strategy = taylortrack::input::ReadFileInputStrategy("../Testdata/Test.wav");
  const char *data = strategy.read();

  std::streampos size_;
  std::ifstream file_ = std::ifstream ("../Testdata/Test.wav", std::ios::in|std::ios::binary|std::ios::ate);
  if(file_.is_open()) {
    size_ = file_.tellg();
    file_.close();
  }

  unsigned long  crc = crc32(0L, Z_NULL, 0);
  crc = crc32(crc, (const unsigned char*) data,size_);

  ASSERT_EQ(true,strategy.is_done());
  ASSERT_EQ(crc,0x22e40972);
}