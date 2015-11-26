#include <yarp/os/all.h>
#include <iostream>
#include "input/input_strategy.h"
#include "input/dummy_input_strategy.h"

const char* test(taylortrack::input::InputStrategy& test) {
    return test.read();
}

int main(int argc, char *argv[]) {
    taylortrack::input::DummyInputStrategy dummy = taylortrack::input::DummyInputStrategy();
    std::cout << test(dummy) << std::endl;

    yarp::os::Network yarp;
    yarp::os::BufferedPort<yarp::os::Bottle> out_port;
    out_port.open("/bp39_out");
    yarp.connect(out_port.getName(),"/bp39_in");
    yarp::os::Bottle& output = out_port.prepare();
    output.clear();
    output.addString("test string");
    out_port.write(true);
}
