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


void PTZSImulator::addPTZ(float filedOfView, float azimuthRotation, float azimuthRotationSpeed, float elevationRotation,
                          float elevationRotationSpeed, float lat, float lon) {
    PTZUnit u(filedOfView, azimuthRotation, azimuthRotationSpeed, elevationRotation, elevationRotationSpeed, lat, lon);
    this->PTZs.push_back(u);
    this->numberOfPTZs++;

}

void PTZSImulator::run() {

}

void PTZSImulator::loadXML(std::string &filename) {

}



void PTZSImulator::enqueue(int fd ,PTZSImulator::command cmd) {
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

PTZSImulator::command PTZSImulator::dequeue() {
    return PTZSImulator::command();
}

void PTZSImulator::initSimulator() {
    initSocket();
    this->executionThread = std::thread(&PTZSImulator::executionLoop,this);
    WaitForConnection();





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
    if(level == WarningLevel::ERROR) exit(1);
}

void PTZSImulator::executionLoop() {
    log("Thread Starts","PTZSImulator::executeCommand",WarningLevel::INFORMATION);
    std::pair<int , PTZSImulator::command> packet ;
    PTZSImulator::command cmd;
    PTZSImulator::feedback feedback;
    while(this->simulationON){
        if(this->commandQueue.size() == 0) continue;
        packet = this->deqeueu();
        cmd = packet.second;
        feedback = this->parse(cmd);
        this->response(packet.first,feedback);





    }
}

std::pair<int ,PTZSImulator::command> PTZSImulator::deqeueu() {
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

PTZSImulator::PTZSImulator(){
    this->socketListenQueueSize = 10;
    this->currentUnit = 0;
    this->listenAddress = "127.0.0.1";
    this->listenPort = 7711;
    this->receiveConnectionOn = 1;
    this->simulationON = 1;

}

void PTZSImulator::receiveLoop(int fd) {
    PTZSImulator::command cmd = {0};
    while(read( fd , (char*)&cmd, sizeof(cmd)) > 0){
        log("Recive Packet","PTZSImulator::receiveLoop",WarningLevel::INFORMATION);
        this->enqueue(fd,cmd);

    }

    log("END of Connection","PTZSImulator::receiveLoop",WarningLevel::INFORMATION);
    close(fd);
}

PTZSImulator::feedback PTZSImulator::parse(PTZSImulator::command) {
    return PTZSImulator::feedback();
}

void PTZSImulator::response(int fd, PTZSImulator::feedback pkt) {

}


