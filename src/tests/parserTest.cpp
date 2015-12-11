#include "../utils/parameter_parser.h"
#include "gtest/gtest.h"
#include <tuple>

TEST(Parsertest,StreamerParserSuccess) {
  int size;
  const char *file;
  const char *testArguments[] = {"../sim_datastreamer", "-s", "42", "path/to/file/file"};
  int argc = 4;

  std::tie(file,size) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_EQ(size,42);
  ASSERT_EQ(file,"path/to/file/file");
}

TEST(ParserTest,StramerParserNoLenght) {
  int size, argc = 2;
  const char *file;
  const char *testArguments[] = {"../sim_datastreamer","path/to/file/file"};
  std::tie(file,size) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_EQ(size,0);
  ASSERT_EQ(file,"path/to/file/file");
}