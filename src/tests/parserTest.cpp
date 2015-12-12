#include "../utils/parameter_parser.h"
#include "gtest/gtest.h"
#include <tuple>

TEST(ParserTest,StreamerParserSuccess) {
  int size;
  const char *file;
  bool valid;
  const char *testArguments[] = {"../sim_datastreamer", "-s", "42", "path/to/file/file"};
  int argc = 4;

  std::tie(file,size,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_TRUE(valid);
  ASSERT_EQ(size,42);
  ASSERT_EQ(file,"path/to/file/file");
}

TEST(ParserTest,StramerParserNoLenght) {
  int size, argc = 2;
  const char *file;
  bool valid;
  const char *testArguments[] = {"../sim_datastreamer","path/to/file/file"};
  std::tie(file,size,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_TRUE(valid);
  ASSERT_EQ(size,0);
  ASSERT_EQ(file,"path/to/file/file");
}

TEST(ParserTest, InvalidParameter) {
  int size, argc = 2;
  const char *file;
  bool valid;
  const char *testArguments[] = {"./sim_datastreamer","-s"};
  std::tie(file,size,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_FALSE(valid);
}