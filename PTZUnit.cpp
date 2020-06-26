//
// Created by level8 on ١٨‏/٦‏/٢٠٢٠.
//

#include <string>
#include "PTZUnit.h"

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
                                                                       lat(lat), lon(lon) {}

PTZUnit::PTZUnit(){}


