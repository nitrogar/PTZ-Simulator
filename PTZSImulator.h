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
class PTZUnit;
class PTZSImulator {



private:
    enum WarningLevel{ERROR,WARNING,INFORMATION};
    std::vector<PTZUnit> PTZs ;
    std::vector<std::pair<std::thread,int >> clientConnectionsThreads;
    std::queue<std::pair<int,Packet::pktCommand>> commandQueue;
    std::vector<std::thread> PTZEnginesThreads;
    std::thread executionThread;
    std::thread waitForConnectionThread;
    int numberOfPTZs;
    int socketListenQueueSize;
    int currentUnit;
    int listenPort;
    int time_elapsed;
    int simulationON;
    int receiveConnectionOn;
    int mainSocketFd;
    int tick = 100;
    std::string listenAddress;

    /*
     * ERROR = Exit program
     * WARNING = Important but dont stop the program
     * INFORMATION = Just to give feedback to the user
     * */

public:
    PTZSImulator();
    void addPTZ(float filedOfView, float azimuthRotation, float azimuthRotationSpeed, float elevationRotation,float elevationRotationSpeed, float lat, float lon,float alt,float range,float phi,float refs);
    void run();
    void initSimulator();
    void loadXML(std::string & filename);
    void initSocket();
    void receiveLoop(int fd) ;
    void WaitForConnection();
    void enqueue(int fd,Packet::pktCommand cmd) ;
    Packet::pktCommand dequeue();
    std::pair<int ,Packet::pktCommand> deqeueu();
    void executionLoop();
    Packet::pktFeedback parse(Packet::pktCommand);
    void response(int fd , Packet::pktFeedback * pkt);
    void log(char * msg, char *  location , PTZSImulator::WarningLevel level);


};


#endif //PTZSIMULATOR_PTZSIMULATOR_H
