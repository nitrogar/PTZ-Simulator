//
// Created by level8 on ٨‏/٧‏/٢٠٢٠.
//

#include "Drone.h"
#include <cmath>
#include <iostream>
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

   if(velocity.x_vec == 0 && velocity.y_vec == 0 && velocity.z_vec == 0)
       return;
    location end = calculateEndLocation(&this->current, &this->velocity,tick);
    double alt = current.altitude + velocity.z_vec * tick/1000;
    current.latitude = end.latitude;
    current.longitude = end.longitude;
    current.altitude = alt;

   // printf("lat : %f , long : %f , alt : %f  x : %f y : %f z : %f\r",current.latitude,current.longitude,current.altitude,velocity.x_vec,velocity.y_vec,velocity.z_vec);
   // fflush(stdout);

}

void Drone::caculateNextLocation() {

}

Drone::location Drone::calculateEndLocation(Drone::location *l, Drone::Vector *vel,double mms) {
    double delta = sqrt((vel->x_vec* vel->x_vec) + (vel->y_vec*vel->y_vec) * mms/1000)/EARTH_RADIUS_IN_METERS;
    double lat = l->latitude * DEG_TO_RAD;
    double lng = l->longitude * DEG_TO_RAD;
    double th0;
   // if(vel->y_vec == 0 && vel->x_vec > 0) th0 = M_PI_2;
   // else if(vel->y_vec && vel->x_vec < 0) th0 = M_PI + M_PI_2;
   // else if(vel->x_vec == 0 && vel->y_vec < 0) th0 = M_PI;
  //  else if(vel->x_vec == 0 && vel->y_vec > 0) th0 = 0;

    //else {
        th0 = atan2(vel->y_vec,vel->x_vec) ;
      //  std::cout << "Test" << std::endl;
  //  }
    th0 = 2* M_PI - th0;
    //std::cout << "Th0 : " << th0 << std::endl;
    double lat2 = asin(sin(lat)*cos(delta) + cos(lat)*sin(delta)*cos(th0));
    lat2 *= 180/M_PI;

    double lng2 = lng + atan2(sin(th0)*sin(delta)*cos(lat),cos(delta)-sin(lat)*sin(lat2));
    lng2 *= 180/M_PI;

    return location{lat2,lng2,0};

}

void Drone::setUnitVector(Drone::Vector *unit) {
    velocity.x_vec = max_vel.x_vec * unit->x_vec;
    velocity.y_vec = max_vel.y_vec * unit->y_vec;
    velocity.z_vec = max_vel.z_vec * unit->z_vec;
    //std::cout << "Inside Unit" << std::endl;

 //   std::cout << "Vector x " <<  velocity.x_vec << " y " << velocity.y_vec << " z " << velocity.z_vec << std::endl ;

}
