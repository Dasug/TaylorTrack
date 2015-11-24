#include <yarp/os/all.h>
#include <iostream>

int main(int argc, char *argv[]) {
    yarp::os::Network yarp;
    yarp::os::BufferedPort<yarp::os::Bottle> out_port;
    out_port.open("/bp39_out");
    yarp.connect(out_port.getName(),"/bp39_in");
    yarp::os::Bottle& output = out_port.prepare();
    output.clear();
    output.addString("test string");
    out_port.write(true);
}