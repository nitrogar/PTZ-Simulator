//
// Created by level8 on ١٩‏/٦‏/٢٠٢٠.
//

#include <netinet/in.h>
#include "PTZSImulator.h"
#include <arpa/inet.h>
#include <map>
#include <thread>
#include <stdio.h>
#include "PTZUnit.h"
#include <unistd.h>
#include <iostream>
#include <utility>
#include <atomic>
void PTZSImulator::addPTZ(float filedOfView, float azimuthRotation, float azimuthRotationSpeed, float elevationRotation,
                          float elevationRotationSpeed, float lat, float lon,float alt,float range,float phi,float ref) {
    PTZUnit u(this->PTZs.size(),filedOfView, azimuthRotation, azimuthRotationSpeed, elevationRotation, elevationRotationSpeed, lat, lon,alt, range, phi, ref);
    this->PTZs.push_back(u);
    PTZUnit * PTZThis = &PTZs[this->numberOfPTZs];
    //std::thread unit(&PTZUnit::runLoop,PTZThis);
    //this->PTZEnginesThreads.push_back(std::move(unit));
    //this->PTZEnginesThreads[this->PTZEnginesThreads.size() - 1].detach();
    this->numberOfPTZs++;
    int t = 0;

}

void PTZSImulator::run() {
    while(true){
        for(int i = 0; i < PTZs.size() ; i++){
            PTZs[i].runSimulation(this->tick);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(this->tick));
    };
}

void PTZSImulator::loadXML(std::string &filename) {

}



void PTZSImulator::enqueue(int fd ,Packet::pktCommand cmd) {
    this->commandQueue.push(std::make_pair(fd,cmd));

}

void PTZSImulator::initSocket() {
    struct sockaddr_in address, clientInfo;
    int opt = 1;
    int addrlen = sizeof(struct sockaddr_in);

    // Creating socket file descriptor
    if ((this->mainSocketFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        log("socket failed","PTZSImulator::initSocket",WarningLevel::ERROR);
    }

    // Forcefully attaching socket to the port 8080

    address.sin_family = AF_INET;
    if(inet_pton(AF_INET, this->listenAddress.c_str(), &address.sin_addr)<=0)
    {
        log("Invalid Address","PTZSImulator::initSocket",WarningLevel::ERROR);
    }
    address.sin_port = htons(this->listenPort);

    if (bind(this->mainSocketFd, (struct sockaddr *)&address,sizeof(address))<0)
    {
        log("Bind Error","PTZSImulator::initSocket",WarningLevel::ERROR);
    }
    if (listen(this->mainSocketFd, this->socketListenQueueSize) < 0)
    {
        log("Error While Listening","PTZSImulator::initSocket",WarningLevel::ERROR);
    }

    log("Finish Socket Initialization","PTZSImulator::initSocket",WarningLevel::INFORMATION);
}

Packet::pktCommand PTZSImulator::dequeue() {
    return Packet::pktCommand();
}

void PTZSImulator::initSimulator() {
    std::cout << sizeof(Packet::pktFeedback) << "--" << sizeof(Packet::pktCommand) << std::endl;
    initSocket();
    this->executionThread = std::thread(&PTZSImulator::executionLoop,this);
    this->waitForConnectionThread = std::thread(&PTZSImulator::WaitForConnection,this);





}

void PTZSImulator::log(char *  msg, char * location, WarningLevel level) {
    switch (level){
        case WarningLevel::INFORMATION :
            printf("[#] ");
            break;
        case WarningLevel::WARNING :
            printf("[*] ");
            break;
        case WarningLevel::ERROR :
            printf("[!] ");
    }

    printf("%s -- (%s)\n",msg,location);
  //  if(level == WarningLevel::ERROR) exit(1);
}

void PTZSImulator::executionLoop() {
    log("Thread Starts","PTZSImulator::executeCommand",WarningLevel::INFORMATION);
    std::pair<int , Packet::pktCommand> packet ;
    Packet::pktCommand cmd;
    Packet::pktFeedback  feedback;
    while(this->simulationON){
        if(this->commandQueue.size() == 0) continue;
        packet = this->deqeueu();
        cmd = packet.second;
        feedback = this->parse(cmd);
        this->response(packet.first,&feedback);

    }
}

std::pair<int ,Packet::pktCommand> PTZSImulator::deqeueu() {
    auto x = this->commandQueue.front();
    this->commandQueue.pop();
    return x;
}

void PTZSImulator::WaitForConnection() {
    struct sockaddr_in clientInfo;
    int new_socket = 0;
    int addrlen = sizeof(struct sockaddr_in);
    char clientAddress[INET_ADDRSTRLEN] = {0};
    char buffer[100] = {0};
    snprintf(buffer,sizeof(buffer),"Waiting For Connections On %s:%d",this->listenAddress.c_str(),this->listenPort);

    log(buffer,"PTZSImulator::WaitForConnection",WarningLevel::INFORMATION);

    while(this->receiveConnectionOn){
        if((new_socket = accept(this->mainSocketFd, (struct sockaddr *)&clientInfo,(socklen_t*)&addrlen))<0)
        {
            log("Cant Accept Connection","PTZSImulator::WaitForConnection",WarningLevel::ERROR);
        }

        inet_ntop(AF_INET, &(clientInfo.sin_addr), clientAddress, INET_ADDRSTRLEN);
        snprintf(buffer,sizeof(buffer),"New Connection from %s at port %d",clientAddress,clientInfo.sin_port);
        log(buffer,"PTZSImulator::WaitForConnection",WarningLevel::INFORMATION);
        this->clientConnectionsThreads.push_back(std::make_pair(std::thread(&PTZSImulator::receiveLoop,this,new_socket),new_socket));
        log("Creating New Thread","PTZSImulator::WaitForConnection",WarningLevel::INFORMATION);



    }
}

PTZSImulator::PTZSImulator():PTZEnginesThreads(0),PTZs(0){
    this->socketListenQueueSize = 10;
    this->currentUnit = 0;
    this->listenAddress = "127.0.0.1";
    this->listenPort = 7766;
    this->receiveConnectionOn = 1;
    this->simulationON = 1;
    this->numberOfPTZs = 0;

}

void PTZSImulator::receiveLoop(int fd) {
    Packet::pktCommand cmd = {0};
    while(read( fd , (char*)&cmd, sizeof(cmd)) > 0){
       // log("Recive Packet","PTZSImulator::receiveLoop",WarningLevel::INFORMATION);
        cmd.cmd = reinterpret_cast<uint8_t >(cmd.cmd);

        this->enqueue(fd,cmd);

    }

    log("END of Connection","PTZSImulator::receiveLoop",WarningLevel::INFORMATION);
    close(fd);
}

Packet::pktFeedback  PTZSImulator::parse(Packet::pktCommand cmd) {
    Packet::pktFeedback fed = {};
    unsigned char PTZIndex = cmd.peripheral - 1;
    float data = 0;
    switch (cmd.cmd){
        case Packet::Command::READ :
           switch (cmd.peripheral_function){
               case Packet::PeripheralFunction::INFORMATION:
                   switch (cmd.action){
                       case Packet::Action::ELEVATION:
                           data = PTZs[PTZIndex].getElevationRotation();
                           break;
                       case Packet::Action::AZIMUTH :
                           data = PTZs[PTZIndex].getAzimuthRotation();
                           break;
                       case Packet::Action::NUMBER_OF_PTZ :
                           data = PTZs.size();
                           break;
                       case Packet::Action::LATITUDE :
                           data = PTZs[PTZIndex].getLat();
                           break;
                       case Packet::Action::LONGITUDE:
                           data = PTZs[PTZIndex].getLon();
                           break;
                       case Packet::Action::AZIMUTH_SPEED:
                           data = PTZs[PTZIndex].getAzimuthRotationSpeed();
                           break;
                       case Packet::Action::ELEVATION_SPEED:
                           data = PTZs[PTZIndex].getElevationRotationSpeed();
                           break;
                       case Packet::Action::ELEVATION_SPEED_FACTOR:
                           data = PTZs[PTZIndex].getElevationSpeedFactor();
                           break;
                       case Packet::Action::AZIMUTH_SPEED_FACTOR :
                           data = data = PTZs[PTZIndex].getAzimuthSpeedFactor();
                           break;

                       case Packet::Action::RANGE :
                           data = data = PTZs[PTZIndex].getRange();
                           break;

                       case Packet::Action::PHI :
                           data = data = PTZs[PTZIndex].getPhi();
                           break;

                       case Packet::Action::ALTITUDE :
                           data = data = PTZs[PTZIndex].getAlt();
                           break;

                       case Packet::Action::REF_FROM_NORTH :
                           data = data = PTZs[PTZIndex].getRefWithNorth();
                           break;

                       default:
                           log("Error defected packet Read/Peripheral_Function/Action Unknown" , "PTZSimulator::parse",WarningLevel::WARNING);

                   }
                   break;
               default:
                   log("Error defected packet Read/Peripheral_Function Unknown" , "PTZSimulator::parse",WarningLevel::WARNING);
           }
            break;
        case Packet::Command::MOVE :
            switch (cmd.peripheral_function){
                case Packet::PeripheralFunction::ELEVATION :
                    PTZs[PTZIndex].setElevationSpeedFactor(cmd.action);
                    break;
                case Packet::PeripheralFunction::AZIMUTH:
                    PTZs[PTZIndex].setAzimuthSpeedFactor(cmd.action);
                    break;
                default:
                    log("Error defected MOVE/Peripheral_Function Unknown" , "PTZSimulator::parse",WarningLevel::WARNING);

            }
            break;
        default:
            printf("Command = %f",cmd.cmd);
            log("Error defected packet Command Unknown" , "PTZSimulator::parse",WarningLevel::WARNING);
    }
    fed.cmd = cmd.cmd;
    fed.peripheral = cmd.peripheral;
    fed.peripheral_function = cmd.peripheral_function;
    fed.action = cmd.action;
    fed.data = data;
    fed.feedback = Packet::Feedback::FLAG;


    return fed;
}

void PTZSImulator::response(int fd, Packet::pktFeedback  * pkt) {
    send(fd,pkt, sizeof(Packet::pktFeedback),0);
}


