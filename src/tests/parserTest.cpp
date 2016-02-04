#include "../utils/parameter_parser.h"
#include "gtest/gtest.h"

TEST(ParserTest,StreamerParserSuccess) {
  int size;
  const char *file;
  bool valid = false;
  const char *testArguments[] = {"../sim_datastreamer", "-s", "42", "path/to/file/file"};
  int argc = 4;

  std::tie(file,size,std::ignore, std::ignore,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_TRUE(valid);
  ASSERT_EQ(size,42);
  ASSERT_EQ(file,"path/to/file/file");
}

TEST(ParserTest,SetOutportTest) {
  const char *testArguments[] = {"../sim_datastreamer", "-o", "/taylortest", "path/to/file/file"};
  int argc = 4;
  bool valid = false;
  const char* outport;
  const char *file;

  std::tie(file,std::ignore,outport, std::ignore,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_TRUE(valid);
  ASSERT_EQ(outport, "/taylortest");
  ASSERT_EQ(file,"path/to/file/file");
}

TEST(ParserTest,SetInportTest) {
  const char *testArguments[] = {"../sim_datastreamer", "-i", "/taylortest", "path/to/file/file"};
  int argc = 4;
  bool valid = false;
  const char* inport;
  const char *file;

  std::tie(file,std::ignore,std::ignore, inport,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_TRUE(valid);
  ASSERT_EQ(inport, "/taylortest");
  ASSERT_EQ(file,"path/to/file/file");
}

TEST(ParserTest,StramerParserNoLenght) {
  int size, argc = 2;
  const char *file;
  bool valid;
  const char *testArguments[] = {"../sim_datastreamer","path/to/file/file"};
  std::tie(file,size,std::ignore, std::ignore,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_TRUE(valid);
  ASSERT_EQ(size,0);
  ASSERT_EQ(file,"path/to/file/file");
}

TEST(ParserTest, InvalidParameter) {
  int size, argc = 2;
  const char *file;
  bool valid;
  const char *testArguments[] = {"./sim_datastreamer","-s"};
  std::tie(file,std::ignore,std::ignore, std::ignore,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_FALSE(valid);
}

TEST(ParserTest, InvalidParameterOutport) {
  int size, argc = 2;
  const char *file;
  bool valid;
  const char *testArguments[] = {"./sim_datastreamer","-o"};
  std::tie(file,std::ignore,std::ignore, std::ignore,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_FALSE(valid);
}

TEST(ParserTest, InvalidParameterInport) {
  int size, argc = 2;
  const char *file;
  bool valid;
  const char *testArguments[] = {"./sim_datastreamer","-i"};
  std::tie(file,std::ignore,std::ignore, std::ignore,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_FALSE(valid);
}

TEST(ParserTest, InvalidParameterName) {
  int argc = 2;
  const char *file;
  const char *testArguments[] = {"./sim_datastreamer","-"};
  bool valid=false;
  std::tie(file,std::ignore,std::ignore, std::ignore,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_FALSE(valid);
}

/*TEST(ParserTest, InvalidParameterName) {
  int argc = 2;
  const char *testArguments[] = {"./sim_datastreamer","-"};
  bool valid=false;
  std::tie(std::ignore,std::ignore,std::ignore, std::ignore,valid) = taylortrack::utils::ParameterParser::parse_streamer(argc,testArguments);
  ASSERT_FALSE(valid);
}*/