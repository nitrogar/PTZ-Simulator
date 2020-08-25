//
// Created by level8 on ٢٩‏/٦‏/٢٠٢٠.
//
#include <cstdint>
#ifndef PTZSIMULATOR_PACKET_H
#define PTZSIMULATOR_PACKET_H
namespace Packet {
    namespace Command {
        const char WRITE = 0x5;
        const char READ = 0x6;
        const char MOVE = 0x7;
        const char DRONE = 0x8;

    }
    namespace PeripheralFunction {
        const char INFORMATION = 0x3;
        const char ELEVATION = 0x1;
        const char AZIMUTH = 0x2;
        const char SET_TARGET_AZIMUTH_UPPER = 0x4;
        const char SET_TARGET_AZIMUTH_LOWER = 0x5;
        const char ADD_TARGET_AZIMUTH_UPPER = 0x6;
        const char ADD_TARGET_AZIMUTH_LOWER = 0x7;

        const char SET_TARGET_ELEVATION_UPPER = 0x8;
        const char SET_TARGET_ELEVATION_LOWER = 0x9;
        const char ADD_TARGET_ELEVATION_UPPER = 0x10;
        const char ADD_TARGET_ELEVATION_LOWER = 0x11;
        const char LOAD_TARGET_AZIMUTH = 0x12;
        const char LOAD_TARGET_ELEVATION = 0x13;
        const char SET_AZIMUTH_SPEED_FACTOR = 0x14;
        const char SET_ELEVATION_SPEED_FACTOR = 0x15;


        const char SET_ELEVATION_SPEED_UPPER = 0x16;
        const char SET_ELEVATION_SPEED_LOWER = 0x17;
        const char SET_AZIMUTH_SPEED_UPPER = 0x18;
        const char SET_AZIMUTH_SPEED_LOWER = 0x19;
        const char LOAD_SPEED_AZIMUTH = 0x1a;
        const char LOAD_SPEED_ELEVATION = 0x1b;

    }
    namespace Action{

        const char ELEVATION = 0x1;
        const char AZIMUTH = 0x2;
        const char NUMBER_OF_PTZ = 0x3;
        const char LONGITUDE = 0x4;
        const char LATITUDE = 0x5;
        const char ELEVATION_SPEED = 0x6;
        const char AZIMUTH_SPEED = 0x7;
        const char ELEVATION_MAX_SPEED = 0x26;
        const char AZIMUTH_MAX_SPEED = 0x27;
        const char ELEVATION_SPEED_FACTOR = 0x8;
        const char AZIMUTH_SPEED_FACTOR = 0x9;
        const char FOV = 0x17;
        const char RANGE = 0x10;
        const char PHI = 0x11;
        const char ALTITUDE = 0x12;
        const char REF_FROM_NORTH = 0x13;
        const char XVEL = 0x14;
        const char YVEL = 0x15;
        const char ZVEL = 0x16;
        const char GET_TARGET_AZIMUTH = 0x19;
        const char GET_TARGET_ELEVATION = 0x18;
    }

    namespace  Feedback {
        const char FLAG = 0x1f;
    }
    struct pktCommand{
        uint8_t cmd;
        uint8_t peripheral;
        uint8_t peripheral_function;
        uint8_t action;
        uint64_t time_stamp;
    }__attribute__((packed));
    struct pktFeedback{
        uint8_t feedback;
        uint8_t cmd;
        uint8_t peripheral;
        uint8_t peripheral_function;
        uint8_t action;

        float data;
        uint64_t time_stamp;
    }__attribute__((packed));

    struct pktVector{
        double x;
        double y;
        double z;
    };
}



#endif //PTZSIMULATOR_PACKET_H
