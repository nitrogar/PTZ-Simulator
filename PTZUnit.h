//
// Created by level8 on ١٨‏/٦‏/٢٠٢٠.
//

#ifndef PTZSIMULATOR_PTZUNIT_H
#define PTZSIMULATOR_PTZUNIT_H


class PTZUnit {
public:
    PTZUnit();

    int saveInXML(std::string & filename) const;
    float getFiledOfView() const;
    float getAzimuthRotation() const;
    float getAzimuthRotationSpeed() const;
    float getElevationRotation() const;
    float getElevationRotationSpeed() const;
    float getLat() const;
    float getLon() const;

    PTZUnit(float filedOfView, float azimuthRotation, float azimuthRotationSpeed, float elevationRotation,
            float elevationRotationSpeed, float lat, float lon);

    void setFiledOfView(float filedOfView);
    void setAzimuthRotation(float azimuthRotation);
    void setAzimuthRotationSpeed(float azimuthRotationSpeed);
    void setElevationRotation(float elevationRotation);
    void setElevationRotationSpeed(float elevationRotationSpeed);
    void setLat(float lat);
    void setLon(float lon);

private:
    float FiledOfView;
    float AzimuthRotation;
    float AzimuthRotationSpeed;
    float ElevationRotation;
    float ElevationRotationSpeed;
    float lat;
    float lon;

};


#endif //PTZSIMULATOR_PTZUNIT_H
