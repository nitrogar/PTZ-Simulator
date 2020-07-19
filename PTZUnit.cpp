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


PTZUnit::PTZUnit(int id ,float filedOfView, float azimuthRotation, float azimuthRotationSpeed, float elevationRotation,
                 float elevationRotationSpeed, float lat, float lon,float alt,float range,float phi,float ref) : FiledOfView(filedOfView),
                                                                       AzimuthRotation(azimuthRotation),
                                                                       AzimuthRotationSpeed(azimuthRotationSpeed),
                                                                       ElevationRotation(elevationRotation),
                                                                       ElevationRotationSpeed(elevationRotationSpeed),
                                                                       lat(lat), lon(lon),speedDividerElevation(0),
                                                                       speedDividerAzimuth(0),azimuthMotorOn(true),
                                                                       elevationMotorOn(true),id(id),alt(alt),range(range),
                                                                       refWithNorth(ref),phi(phi)
                                                                       {this->tick=1000;this->targetAngelElevation=ElevationRotation;
                                                                       this->targetAngelAzimuth=AzimuthRotation;
                                                                       this->speedDividerAzimuth = 1;
                                                                       this->speedDividerElevation = 1;}

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
void PTZUnit::runSimulation(float timeElapsed) {
          //  std::cout << "id : " << id << " Target Az : " << targetAngelAzimuth << " Target El " << targetAngelElevation << std::endl;
            if (elevationMotorOn && this->getElevationSpeedFactor()!= 0){
                if(abs(this->ElevationRotation - this->targetAngelElevation) > 0.01)
                    if(this->ElevationRotation < this->targetAngelElevation)
                        this->setElevationRotation(fmod((this->getElevationRotation() +(timeElapsed / 1000.0f) * this->getElevationRotationSpeed() *(1.0f / this->getElevationSpeedFactor())), 360.0f));
                    else if( this->ElevationRotation > this->targetAngelElevation)
                        this->setElevationRotation(fmod((this->getElevationRotation() -(timeElapsed / 1000.0f) * this->getElevationRotationSpeed() *(1.0f / this->getElevationSpeedFactor())), 360.0f));



            }
            if (azimuthMotorOn && speedDividerAzimuth != 0){
                if(abs(this->AzimuthRotation - this->targetAngelAzimuth) > 0.01)
                    if(this->AzimuthRotation < this->targetAngelAzimuth)
                        this->AzimuthRotation = fmod((this->AzimuthRotation + (timeElapsed / 1000.0f) * this->AzimuthRotationSpeed * (1.0f / this->speedDividerAzimuth)) , 360.0f);
                    else if( this->AzimuthRotation > this->targetAngelAzimuth)
                        this->AzimuthRotation = fmod((this->AzimuthRotation - (timeElapsed / 1000.0f) * this->AzimuthRotationSpeed * (1.0f / this->speedDividerAzimuth)) , 360.0f);

            }

}

volatile float PTZUnit::getAlt() const {
    return alt;
}

void PTZUnit::setAlt(volatile float alt) {
    this->alt = alt;
}

volatile float PTZUnit::getPhi() const {
    return phi;
}

void PTZUnit::setPhi(volatile float phi) {
    this->phi = phi;
}

volatile float PTZUnit::getRange() const {
    return range;
}

void PTZUnit::setRange(volatile float range) {
    this->range = range;
}

volatile float PTZUnit::getRefWithNorth() const {
    return refWithNorth;
}

void PTZUnit::setRefWithNorth(volatile float refWithNorth) {
    this->refWithNorth = refWithNorth;
}


float PTZUnit::getTargetAngelAzimuth() const {
    return targetAngelAzimuth;
}

void PTZUnit::setTargetAngelAzimuth(float targetAngelAzimuth) {
    PTZUnit::targetAngelAzimuth = targetAngelAzimuth;
}

float PTZUnit::getTargetAngelElevation() const {
    return targetAngelElevation;
}

void PTZUnit::setTargetAngelElevation(float targetAngelElevation) {
    PTZUnit::targetAngelElevation = targetAngelElevation;
}

void PTZUnit::addTargetElevationLower(char ang) {
    float fang = (float) ang;
    fang = fang / 100;
    this->targetAngelElevation += fang;
}

void PTZUnit::addTargetElevationUpper(char ang) {
    float fang = (float) ang;
    this->targetAngelElevation += fang;
}

void PTZUnit::setTargetElevationLower(char ang) {
    int top = (int) this->targetAngelElevation;
    float lower = (float)ang;
    lower = lower/100;
    this->targetAngelElevation = (float)top + lower;
}

void PTZUnit::setTargetElevationUpper(char ang) {
    int top = (float) ang;
    float lower = (float)(this->targetAngelElevation - (int) this->targetAngelElevation);

    this->targetAngelElevation = top + lower;

}

void PTZUnit::addTargetAzimuthLower(char ang) {
    float fang = (float) ang;
    fang = fang / 100;
    this->targetAngelAzimuth += ang;
}

void PTZUnit::addTargetAzimuthUpper(char ang) {
    float fang = (float) ang;
   // std::cout << fang << std::endl;
    this->targetAngelAzimuth += fang;
}

void PTZUnit::setTargetAzimuthLower(char ang) {
    int top = (int) this->targetAngelAzimuth;
    float lower = (float)ang;
    lower = lower/100;


    this->targetAngelAzimuth = (float)top + lower;
}

void PTZUnit::setTargetAzimuthUpper(char ang) {
    int top = (float) ang;
    float lower = (float)(this->targetAngelAzimuth - (int) this->targetAngelAzimuth);

    this->targetAngelAzimuth = top + lower;
}


