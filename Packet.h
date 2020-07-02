//
// Created by level8 on ٢٩‏/٦‏/٢٠٢٠.
//
#include <cstdint>
#ifndef PTZSIMULATOR_PACKET_H
#define PTZSIMULATOR_PACKET_H
namespace Packet {
    namespace Command {
        const char READ = 0x6;
        const char MOVE = 0x7;
    }
    namespace PeripheralFunction {
        const char INFORMATION = 0x3;
        const char ELEVATION = 0x1;
        const char AZIMUTH = 0x2;
    }
    namespace Action{

        const char ELEVATION = 0x1;
        const char AZIMUTH = 0x2;
        const char NUMBER_OF_PTZ = 0x3;
        const char LONGITUDE = 0x4;
        const char LATITUDE = 0x5;
        const char ELEVATION_SPEED = 0x6;
        const char AZIMUTH_SPEED = 0x7;
        const char ELEVATION_SPEED_FACTOR = 0x8;
        const char AZIMUTH_SPEED_FACTOR = 0x9;

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

}



#endif //PTZSIMULATOR_PACKET_H
