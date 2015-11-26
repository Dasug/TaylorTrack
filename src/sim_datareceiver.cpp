#include <yarp/os/all.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    yarp::os::Network yarp;
    yarp::os::BufferedPort<yarp::os::Bottle> port;
    port.open("/bp39_in");
    unsigned int timeout = 3000000;
    while (true) {
        std::cout << "waiting for input" << std::endl;
        yarp::os::Bottle *input = port.read();
        if (input!=NULL) {
            std::cout << "got message (length " << input->toString().size() << "):" << input->toString().c_str() << std::endl;
        }
    }
    return 0;
}
