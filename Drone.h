//
// Created by level8 on ٨‏/٧‏/٢٠٢٠.
//

#ifndef PTZSIMULATOR_DRONE_H
#define PTZSIMULATOR_DRONE_H


class Drone {

public:
    struct location{
        double latitude;
        double longitude;
        double altitude;
    };

    struct Vector{
        double x_vec;
        double y_vec;
        double z_vec;
    };
    double getLatitude() const;
    void setLatitude(double latitude);
    double getLongitude() const;
    void setLongitude(double longitude);
    double getAltitude() const;
    void setAltitude(double altitude);
    double getXVec() const;
    void setXVec(double xVec);
    double getYVec() const;
    void setYVec(double yVec);
    double getZVec() const;
    void setZVec(double zVec);
    void caculateNextLocation();
    void runSimulation(int tick);
    void calculateEndLocation(location * l , Vector * vel );
    Drone(double latitude, double longitude, double altitude);
    Drone(double latitude, double longitude, double altitude, double xVec, double yVec, double zVec);
    Drone();

    const double DEG_TO_RAD = 0.017453292519943295769236907684886;
    const double EARTH_RADIUS_IN_METERS = 6372797.560856;

private:

    location current;
    Vector velocity;


};


#endif //PTZSIMULATOR_DRONE_H
