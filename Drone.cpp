//
// Created by level8 on ٨‏/٧‏/٢٠٢٠.
//

#include "Drone.h"

double Drone::getLatitude() const {
    return current.latitude;
}

void Drone::setLatitude(double latitude) {
    current.latitude = latitude;
}

double Drone::getLongitude() const {
    return current.longitude;
}

void Drone::setLongitude(double longitude) {
    current.longitude = longitude;
}

double Drone::getAltitude() const {
    return current.altitude;
}

void Drone::setAltitude(double altitude) {
    current.altitude = altitude;
}

double Drone::getXVec() const {
    return velocity.x_vec;
}

void Drone::setXVec(double xVec) {
    velocity.x_vec = xVec;
}

double Drone::getYVec() const {
    return velocity.y_vec;
}

void Drone::setYVec(double yVec) {
    velocity.y_vec = yVec;
}

double Drone::getZVec() const {
    return velocity.z_vec;
}

void Drone::setZVec(double zVec) {
    velocity.z_vec = zVec;
}

Drone::Drone(double latitude, double longitude, double altitude, double xVec, double yVec, double zVec) {
    current.altitude = altitude;
    current.longitude = longitude;
    current.latitude = latitude;
    velocity.x_vec = xVec;
    velocity.y_vec = yVec;
    velocity.z_vec = zVec;

}

Drone::Drone(double latitude, double longitude, double altitude){
    current.altitude = altitude;
    current.longitude = longitude;
    current.latitude = latitude;
}

Drone::Drone() {}

void Drone::runSimulation(int tick) {

}

void Drone::caculateNextLocation() {

}

void Drone::calculateEndLocation(Drone::location *l, Drone::Vector *vel) {
    double delta = this->range/EARTH_RADIUS_IN_METERS;
    double lat = this->latitude * DEG_TO_RAD;
    double lng = this->longitude * DEG_TO_RAD;
    double th0 = angle ;//this->angleFromNorth - angle;
    // if(th0 < 0) th0 += 360;
    th0 *= DEG_TO_RAD;

    double lat2 = asin(sin(lat)*cos(delta) + cos(lat)*sin(delta)*cos(th0));
    lat2 *= 180/M_PI;

    double lng2 = lng + atan2(sin(th0)*sin(delta)*cos(lat),cos(delta)-sin(lat)*sin(lat2));
    lng2 *= 180/M_PI;
    return QGeoCoordinate(lat2,lng2);

}
