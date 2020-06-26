#include <iostream>
#include "PTZSImulator.h"
int main() {
    PTZSImulator sim;
    sim.initSimulator();
  //  sim.addPTZ();
    sim.run();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
