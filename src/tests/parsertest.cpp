#include "gtest/gtest.h"
#include "../utils/parameter_parser.h"

TEST(ParserTest, StreamerParserSuccess) {
  const char *testArguments[] = {"../sim_datastreamer", "-s", "42", "path/to/file/file"};
  int argc = 4;

  taylortrack::utils::Parameters parameters = taylortrack::utils::ParameterParser::parse_streamer(argc, testArguments);
  ASSERT_TRUE(parameters.valid);
  ASSERT_EQ(parameters.size, 42);
  ASSERT_EQ(parameters.file, "path/to/file/file");
}

TEST(ParserTest, SetOutportTest) {
  const char *testArguments[] = {"../sim_datastreamer", "-o", "/taylortest", "path/to/file/file"};
  int argc = 4;

  taylortrack::utils::Parameters parameters = taylortrack::utils::ParameterParser::parse_streamer(argc, testArguments);
  ASSERT_TRUE(parameters.valid);
  ASSERT_EQ(parameters.outport, "/taylortest");
  ASSERT_EQ(parameters.file, "path/to/file/file");
}

TEST(ParserTest, SetInportTest) {
  const char *testArguments[] = {"../sim_datastreamer", "-i", "/taylortest", "path/to/file/file"};
  int argc = 4;

  taylortrack::utils::Parameters parameters = taylortrack::utils::ParameterParser::parse_streamer(argc, testArguments);
  ASSERT_TRUE(parameters.valid);
  ASSERT_EQ(parameters.inport, "/taylortest");
  ASSERT_EQ(parameters.file, "path/to/file/file");
}

TEST(ParserTest, StramerParserNoLenght) {
  int argc = 2;
  const char *testArguments[] = {"../sim_datastreamer", "path/to/file/file"};

  taylortrack::utils::Parameters parameters = taylortrack::utils::ParameterParser::parse_streamer(argc, testArguments);
  ASSERT_TRUE(parameters.valid);
  ASSERT_EQ(parameters.size, 0);
  ASSERT_EQ(parameters.file, "path/to/file/file");
}

TEST(ParserTest, InvalidParameter) {
  int argc = 2;
  const char *testArguments[] = {"./sim_datastreamer", "-s"};

  taylortrack::utils::Parameters parameters = taylortrack::utils::ParameterParser::parse_streamer(argc, testArguments);
  ASSERT_FALSE(parameters.valid);
}

TEST(ParserTest, InvalidParameterOutport) {
  int argc = 2;
  const char *testArguments[] = {"./sim_datastreamer", "-o"};

  taylortrack::utils::Parameters parameters = taylortrack::utils::ParameterParser::parse_streamer(argc, testArguments);
  ASSERT_FALSE(parameters.valid);
}

TEST(ParserTest, InvalidParameterInport) {
  int argc = 2;
  const char *testArguments[] = {"./sim_datastreamer", "-i"};

  taylortrack::utils::Parameters parameters = taylortrack::utils::ParameterParser::parse_streamer(argc, testArguments);
  ASSERT_FALSE(parameters.valid);
}

TEST(ParserTest, InvalidParameterName) {
  int argc = 2;
  const char *testArguments[] = {"./sim_datastreamer", "-"};

  taylortrack::utils::Parameters parameters = taylortrack::utils::ParameterParser::parse_streamer(argc, testArguments);
  ASSERT_FALSE(parameters.valid);
}