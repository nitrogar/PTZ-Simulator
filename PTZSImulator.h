//
// Created by level8 on ١٩‏/٦‏/٢٠٢٠.
//

#ifndef PTZSIMULATOR_PTZSIMULATOR_H
#define PTZSIMULATOR_PTZSIMULATOR_H

#include <vector>
#include <thread>
#include <queue>
#include <map>
#include <string>
#include "PTZUnit.h"
#include "Packet.h"
#include "Drone.h"
class PTZUnit;
class PTZSImulator {



private:
    enum WarningLevel{ERROR,WARNING,INFORMATION};
    std::vector<Drone> drones ;
    std::vector<PTZUnit> PTZs ;
    std::vector<std::pair<std::thread,int >> clientConnectionsThreads;
    std::queue<std::pair<int,Packet::pktCommand>> commandQueue;
    std::vector<std::thread> PTZEnginesThreads;
    std::thread executionThread;
    std::thread waitForConnectionThread;
    std::thread droneInputThread;
    int numberOfPTZs;
    int socketListenQueueSize;
    int currentUnit;
    int listenPort;
    int time_elapsed;
    int simulationON;
    int receiveConnectionOn;
    int mainSocketFd;
    int tick = 20;
    std::string listenAddress;

    /*
     * ERROR = Exit program
     * WARNING = Important but dont stop the program
     * INFORMATION = Just to give feedback to the user
     * */

public:
    PTZSImulator();
    void addPTZ(float filedOfView, float azimuthRotation, float azimuthRotationSpeed, float elevationRotation,float elevationRotationSpeed, float lat, float lon,float alt,float range,float phi,float refs);
    void addDrone(double lat, double lng,double alt);
    void run();
    void initSimulator();
    void loadXML(std::string & filename);
    void initSocket();
    void receiveLoop(int fd) ;
    void WaitForConnection();
    void enqueue(int fd,Packet::pktCommand cmd) ;
    void droneInput();
    Packet::pktCommand dequeue();
    std::pair<int ,Packet::pktCommand> deqeueu();
    void executionLoop();
    Packet::pktFeedback parse(Packet::pktCommand);
    void response(int fd , Packet::pktFeedback * pkt);
    void log(const char * msg, const char *  location , PTZSImulator::WarningLevel level);


};


#endif //PTZSIMULATOR_PTZSIMULATOR_H
