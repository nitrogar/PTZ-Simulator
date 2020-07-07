#include <iostream>
#include "PTZSImulator.h"
int main() {
    PTZSImulator sim;
    sim.initSimulator();
    sim.addPTZ(45.0f, 50.0f, 10.0f, 40.0f, 10.0f, 24.688498,46.691351,3,250,90,90);

    sim.addPTZ(45.0f, 110.0f, 10.0f, 22.0f, 10.0f, 24.80452,46.75649,1,100,90,45);

    sim.addPTZ(120.0f, 20.0f, 10.0f, 15.0f, 10.0f, 24.673207,46.68809,2,50,120,150);

    sim.addPTZ(90.0f, 40.0f, 10.0f, 43.0f, 10.0f, 24.685052,46.696362,4,40,120,0);

   // sim.addPTZ(45.0f, 50.0f, 10.0f, 40.0f, 10.0f, 24.688498,46.691351);

    //sim.addPTZ(45.0f, 110.0f, 10.0f, 22.0f, 10.0f, 24.80452,46.75649);

    //sim.addPTZ(120.0f, 20.0f, 10.0f, 15.0f, 10.0f, 24.673207,46.68809);

    sim.run();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
