//
// Created by level8 on ١٨‏/٦‏/٢٠٢٠.
//

#include <string>
#include "PTZUnit.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <unistd.h>
float PTZUnit::getFiledOfView() const {
    return FiledOfView;
}

float PTZUnit::getAzimuthRotation() const {
    return AzimuthRotation;
}

float PTZUnit::getAzimuthRotationSpeed() const {
    return AzimuthRotationSpeed;
}

float PTZUnit::getElevationRotation() const {
    return ElevationRotation;
}
float PTZUnit::getAzimuthSpeedFactor() const {
    return speedDividerAzimuth;
}
float PTZUnit::getElevationSpeedFactor() const {
    return speedDividerElevation;
}



float PTZUnit::getElevationRotationSpeed() const {
    return ElevationRotationSpeed;
}

float PTZUnit::getLat() const {
    return lat;
}

float PTZUnit::getLon() const {
    return lon;
}

void PTZUnit::setFiledOfView(float filedOfView) {
    FiledOfView = filedOfView;
}

void PTZUnit::setAzimuthRotation(float azimuthRotation) {
    AzimuthRotation = azimuthRotation;
}

void PTZUnit::setAzimuthRotationSpeed(float azimuthRotationSpeed) {
    AzimuthRotationSpeed = azimuthRotationSpeed;
}

void PTZUnit::setElevationRotation(float elevationRotation) {
    ElevationRotation = elevationRotation;
}

void PTZUnit::setElevationRotationSpeed(float elevationRotationSpeed) {
    ElevationRotationSpeed = elevationRotationSpeed;
}

void PTZUnit::setLat(float lat) {
    PTZUnit::lat = lat;
}

void PTZUnit::setLon(float lon) {
    PTZUnit::lon = lon;
}

int PTZUnit::saveInXML(std::string &filename) const {
    return 0;
}


PTZUnit::PTZUnit(float filedOfView, float azimuthRotation, float azimuthRotationSpeed, float elevationRotation,
                 float elevationRotationSpeed, float lat, float lon) : FiledOfView(filedOfView),
                                                                       AzimuthRotation(azimuthRotation),
                                                                       AzimuthRotationSpeed(azimuthRotationSpeed),
                                                                       ElevationRotation(elevationRotation),
                                                                       ElevationRotationSpeed(elevationRotationSpeed),
                                                                       lat(lat), lon(lon),speedDividerElevation(0),
                                                                       speedDividerAzimuth(0),azimuthMotorOn(true),
                                                                       elevationMotorOn(true){this->tick=100;}

PTZUnit::PTZUnit(){}

void PTZUnit::setElevationSpeedFactor(char factor) {
        this->speedDividerElevation = factor;
}

void PTZUnit::setAzimuthSpeedFactor(char factor) {
    this->speedDividerAzimuth = factor;

}

void PTZUnit::log(char *  msg, char * location, WarningLevel level) {
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
void PTZUnit::runLoop() {
    log("Starting PTZ thread" , "PTZUnit::runLoop",WarningLevel::INFORMATION);
    //std::chrono::duration<float, std::milli> delta ;
    //auto past = std::chrono::system_clock::now().time_since_epoch();
    while(true) {
     //   if (delta.count() > 100) {
           //past = std::chrono::system_clock::now().time_since_epoch();
            if (elevationMotorOn && speedDividerElevation != 0) {
                this->ElevationRotation = fmod((this->ElevationRotation +(this->tick / 1000.0f) * this->ElevationRotationSpeed *(1.0f / this->speedDividerElevation)), 360.0f);
            }
            if (azimuthMotorOn && speedDividerAzimuth != 0)
                this->AzimuthRotation = fmod((this->AzimuthRotation + (this->tick / 1000.0f) * this->AzimuthRotationSpeed * (1.0f / this->speedDividerAzimuth)) , 360.0f);
          //  std::cout << "Time elabsed " << delta.count()<< std::endl;

       // }
       // delta = std::chrono::system_clock::now().time_since_epoch() - past;
      // std::cout << "Elevatin : " << this->ElevationRotation << " Azimuth : " << this->AzimuthRotation << std::endl;
       //std::cout << "elavationInfo : " << elevationMotorOn << " - " << +speedDividerElevation << " AzimuthInfo : " <<  azimuthMotorOn << " - "<< +speedDividerAzimuth << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(this->tick));
    }
}


