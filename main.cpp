#include <iostream>
#include "PTZSImulator.h"
int main() {
    PTZSImulator sim;
    sim.initSimulator();
    sim.addPTZ(45.0f, 50.0f, 10.0f, 40.0f, 10.0f, 24.449693, 39.631465);
    sim.addPTZ(45.0f, 110.0f, 10.0f, 22.0f, 10.0f, 24.80452,46.75649);
    sim.addPTZ(120.0f, 20.0f, 10.0f, 15.0f, 10.0f, 24.8118,46.66038);
    sim.addPTZ(90.0f, 40.0f, 10.0f, 43.0f, 10.0f, 13.19,24.7832);

    sim.run();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
