/*
The MIT License (MIT)

Copyright (c) 2015 Marius Kaufmann, Tamara Frieß, Jannis Hoppe, Christian Hack

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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

  void DummyInputStrategy::set_parameters(const utils::Parameters &params) {
    // do nothing, we don't care about parameters
  }

  void DummyInputStrategy::set_config(const utils::ConfigParser &config_parser) {
    // do nothing, we don't care about configuration either
  }
}  // namespace input
}  // namespace taylortrack
