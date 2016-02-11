#include <iomanip>
#include "config_parser.h"

taylortrack::utils::ConfigParser::ConfigParser(const char *file_name) {
  file_ = std::ifstream(file_name, std::ios::in|std::ios::binary);
  valid = true;
  parse_file();
}

void taylortrack::utils::ConfigParser::parse_file() {
  // 0 = options, 1 = audio, 2 = video, 3 = combination
  int section = -1;
  std::string line;
  while(std::getline(file_,line)) {
    std::vector<std::string> x = split(line,'=');
    if(x.size() != 2 && line.find('[') == std::string::npos)
      continue;

    if(section == 0 && (!line.empty() && line.at(0) != '[' && line.at(0) != '#' && !isspace(line.at(0)))) {
      x[0] = trim(x[0]);
      x[1] = trim(x[1]);

      if(x[0].compare("console_output") == 0)
        options.console_output = x[1].compare("true") == 0;

    }else if(section == 1 && (!line.empty() && line.at(0) != '[' && line.at(0) != '#' && !isspace(line.at(0)))) {
      x[0] = trim(x[0]);
      x[1] = trim(x[1]);

      if (x[0].compare("inport") == 0)
        audio.inport = x[1];
      else if (x[0].compare("outport") == 0)
        audio.outport = x[1];
      else if (x[0].compare("sample_rate") == 0)
        std::istringstream(x[1]) >> audio.sample_rate;
      else if (x[0].compare("mic_x") == 0) { // TODO handle multiple whitespaces and tabs
        std::vector<std::string> mic = split(x[1],' ');
        audio.mic_x.resize(mic.size());
        for(uint i = 0; i < mic.size(); i++)
          std::stringstream(mic[i]) >> audio.mic_x[i];
      }else if (x[0].compare("mic_y") == 0) { // TODO handle multiple whitespaces and tabs
        std::vector<std::string> mic = split(x[1],' ');
        audio.mic_y.resize(mic.size());
        for(uint i = 0; i < mic.size(); i++)
          std::stringstream(mic[i]) >> audio.mic_y[i];
      }else if(x[0].compare("beta") == 0)
        std::stringstream(x[1]) >> audio.beta;
      else if(x[0].compare("grid_x") == 0)
        std::stringstream(x[1]) >> audio.grid_x;
      else if(x[0].compare("grid_y") == 0)
        std::stringstream(x[1]) >> audio.grid_y;
      else if(x[0].compare("interval") == 0)
        std::stringstream(x[1]) >> audio.interval;
      else if(x[0].compare("frame_size") == 0)
        std::stringstream(x[1]) >> audio.frame_size;
    } // end if section 1
    else if(section == 2 && (!line.empty() && line.at(0) != '[' && line.at(0) != '#' && !isspace(line.at(0)))) {
      x[0] = trim(x[0]);
      x[1] = trim(x[1]);

      if (x[0].compare("inport") == 0)
        video.inport = x[1];
      else if (x[0].compare("outport") == 0)
        video.outport = x[1];

    } // end if section 2
    else if(section == 3 && (!line.empty() && line.at(0) != '[' && line.at(0) != '#' && !isspace(line.at(0)))) {
      x[0] = trim(x[0]);
      x[1] = trim(x[1]);

      if (x[0].compare("inport") == 0)
        combination.inport = x[1];
      else if (x[0].compare("outport") == 0)
        combination.outport = x[1];
    } // end if section 3

    if(line.compare("[options]") == 0)
      section = 0;
    else if(line.compare("[audio]") == 0)
      section = 1;
    else if(line.compare("[video]") == 0)
      section = 2;
    else if(line.compare("[combination]") == 0)
      section = 3;
  } // end while
  if(audio.mic_x.size() != audio.mic_y.size())
    valid = false;
}

// Method to split a string by the given delim.
std::vector<std::string> taylortrack::utils::ConfigParser::split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  std::stringstream ss(s);
  std::string item;

  while(std::getline(ss,item,delim))
    elems.push_back(item);

  return elems;
}

// Method to remove whitespacese, tabulator etc. from the the front and back of the string.
std::string taylortrack::utils::ConfigParser::trim(const std::string &s) {
  auto wsfront = std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
  auto wsback = std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();

  return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
}
