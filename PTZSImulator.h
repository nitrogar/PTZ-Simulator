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
class PTZUnit;
class PTZSImulator {

    struct command{
        uint8_t cmd;
        uint8_t perihpheral;
        uint8_t function;
        uint8_t action;
        uint64_t time_stamp;
    };
    struct feedback{
        uint8_t feedback;
        uint8_t cmd;
        uint8_t perihpheral;
        uint8_t function;
        uint8_t action;
        float data;
        uint64_t time_stamp;
    };

private:
    enum WarningLevel{ERROR,WARNING,INFORMATION};
    std::vector<PTZUnit> PTZs ;
    std::vector<std::pair<std::thread,int >> clientConnectionsThreads;
    std::queue<std::pair<int,command>> commandQueue;
    //std::map<std::string, void(PTZSImulator::*fn)(std::string)> reflection;
    std::thread executionThread;
    int numberOfPTZs;
    int socketListenQueueSize;
    int currentUnit;
    int listenPort;
    int time_elapsed;
    int simulationON;
    int receiveConnectionOn;
    int mainSocketFd;
    std::string listenAddress;

    /*
     * ERROR = Exit program
     * WARNING = Important but dont stop the program
     * INFORMATION = Just to give feedback to the user
     * */

public:
    PTZSImulator();
    void addPTZ(float filedOfView, float azimuthRotation, float azimuthRotationSpeed, float elevationRotation,float elevationRotationSpeed, float lat, float lon);
    void run();
    void initSimulator();
    void loadXML(std::string & filename);
    void initSocket();
    void receiveLoop(int fd) ;
    void WaitForConnection();
    void enqueue(int fd,PTZSImulator::command cmd) ;
    PTZSImulator::command dequeue();
    std::pair<int ,PTZSImulator::command> deqeueu();
    void executionLoop();
    PTZSImulator::feedback parse(PTZSImulator::command);
    void response(int fd , PTZSImulator::feedback pkt);
    void log(char * msg, char *  location , PTZSImulator::WarningLevel level);


};


#endif //PTZSIMULATOR_PTZSIMULATOR_H
