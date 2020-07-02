//
// Created by level8 on ١٨‏/٦‏/٢٠٢٠.
//

#ifndef PTZSIMULATOR_PTZUNIT_H
#define PTZSIMULATOR_PTZUNIT_H


class PTZUnit {
public:
    enum WarningLevel{ERROR,WARNING,INFORMATION};

    PTZUnit();
    int saveInXML(std::string & filename) const;
    float getFiledOfView() const;
    float getAzimuthRotation() const;
    float getAzimuthRotationSpeed() const;
    float getElevationRotation() const;
    float getElevationRotationSpeed() const;
    float getLat() const;
    float getLon() const;
    float getAzimuthSpeedFactor() const;
    float getElevationSpeedFactor() const;
    PTZUnit(float filedOfView, float azimuthRotation, float azimuthRotationSpeed, float elevationRotation,
            float elevationRotationSpeed, float lat, float lon);

    void setFiledOfView(float filedOfView);
    void setAzimuthRotation(float azimuthRotation);
    void setAzimuthRotationSpeed(float azimuthRotationSpeed);
    void setElevationRotation(float elevationRotation);
    void setElevationRotationSpeed(float elevationRotationSpeed);
    void setElevationSpeedFactor(char factor);
    void setAzimuthSpeedFactor(char factor);
    void setLat(float lat);
    void setLon(float lon);
    void log(char *  msg, char * location, WarningLevel level);
    void runLoop();

private:
    int tick;
    float FiledOfView;
    float AzimuthRotation;
    float AzimuthRotationSpeed;
    float ElevationRotation;
    float ElevationRotationSpeed;
    float lat;
    float lon;
    bool elevationMotorOn;
    bool azimuthMotorOn;
    uint8_t speedDividerElevation;
    uint8_t  speedDividerAzimuth;

};


#endif //PTZSIMULATOR_PTZUNIT_H
