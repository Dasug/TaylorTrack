/**
* @file
* @brief Implementation of the dummy_input_strategy.h
*/

#include "dummy_input_strategy.h"

namespace taylortrack {
  namespace input {
    DummyInputStrategy::DummyInputStrategy() {
      done_ = false;
    }

    yarp::os::Bottle DummyInputStrategy::read(yarp::os::Bottle &bottle) {
      done_ = true;
      bottle.addString("Dummy Test successful");
      return bottle;
    }

    bool DummyInputStrategy::is_done() {
      return done_;
    }
  }
}
