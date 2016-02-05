//
// Created by christian on 05.02.16.
//

#ifndef TAYLORTRACK_PARAMETERS_H
#define TAYLORTRACK_PARAMETERS_H

struct Parameters {
  const char *file;
  const char *outport = "/bp39_out";
  const char *inport = "/bp39_in";
  int size = 0;
  bool valid = false;
};
#endif //TAYLORTRACK_PARAMETERS_H
