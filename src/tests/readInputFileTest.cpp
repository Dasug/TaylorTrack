#include "../utils/parameter_parser.h"
#include "gtest/gtest.h"
#include "zlib.h"
#include "../input/read_file_input_strategy.h"

TEST(InputFileTest,CRC32Match) {
  taylortrack::input::ReadFileInputStrategy strategy = taylortrack::input::ReadFileInputStrategy("../src/tests/Test.txt");
  const char *data = strategy.read();
  unsigned long  crc = crc32(0L, Z_NULL, 0);
  crc = crc32(crc, (const unsigned char*) data,(strlen(data)));

  ASSERT_EQ(true,strategy.is_done());
  ASSERT_EQ(crc,0x56e3bce3);
}

TEST(InputFileTest,ReadTwoTimes) {
  taylortrack::input::ReadFileInputStrategy strategy = taylortrack::input::ReadFileInputStrategy("../src/tests/Test.txt");
  const char *data = strategy.read();
  ASSERT_EQ(true, strategy.is_done());
  data = strategy.read();
  unsigned long  crc = crc32(0L, Z_NULL, 0);
  crc = crc32(crc, (const unsigned char*) data,(strlen(data)));

  ASSERT_EQ(crc,0x56e3bce3);
  ASSERT_EQ(true, strategy.is_done());
}

TEST(InputFileTest,NoFile) {
  taylortrack::input::ReadFileInputStrategy *strategy = new taylortrack::input::ReadFileInputStrategy("nodata");

  ASSERT_EQ(NULL,strategy ->read());
  ASSERT_EQ(true,strategy -> is_done());
}