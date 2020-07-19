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
    PTZUnit(int id ,float filedOfView, float azimuthRotation, float azimuthRotationSpeed, float elevationRotation,
            float elevationRotationSpeed, float lat, float lon ,float alt,float range,float phi,float ref);

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
    void runSimulation(float timeElapsed);

private:
    int id;
    int tick;
    float FiledOfView;
    float AzimuthRotation;
    float AzimuthRotationSpeed;
    float ElevationRotation;
    float ElevationRotationSpeed;
    float lat;
    float lon;
    float alt;
    float phi;
    float range;
    float refWithNorth;
    float targetAngelAzimuth;
    float targetAngelElevation;
public:
    float getTargetAngelAzimuth() const;

    void setTargetAngelAzimuth(float targetAngelAzimuth);

    float getTargetAngelElevation() const;

    void setTargetAngelElevation(float targetAngelElevation);

public:
    float getTargetAngel() const;

    void setTargetAngel(float targetAngel);
    void addTargetElevationLower(char ang);
    void addTargetElevationUpper(char ang);
    void setTargetElevationLower(char ang);
    void setTargetElevationUpper(char ang);

    void addTargetAzimuthLower(char ang);
    void addTargetAzimuthUpper(char ang);
    void setTargetAzimuthLower(char ang);
    void setTargetAzimuthUpper(char ang);


public:
    volatile float getRefWithNorth() const;

    void setRefWithNorth(volatile float refWithNorth);

public:
    volatile float getAlt() const;

    void setAlt(volatile float alt);

    volatile float getPhi() const;

    void setPhi(volatile float phi);

    volatile float getRange() const;

    void setRange(volatile float range);

private:
    volatile  bool elevationMotorOn;
    volatile bool azimuthMotorOn;
    volatile uint8_t speedDividerElevation;
    volatile uint8_t  speedDividerAzimuth;

};


#endif //PTZSIMULATOR_PTZUNIT_H
