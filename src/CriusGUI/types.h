#ifndef TYPES
#define TYPES

#include <stdint.h>

struct Vec3i16
{
    int16_t x;
    int16_t y;
    int16_t z;
};

struct Quaternion
{
    double q0;
    double q1;
    double q2;
    double q3;
};

struct StatusData
{
    uint32_t timeStamp;
    uint16_t cycleTime;
};

struct RCData
{
    uint16_t throttle;
    uint16_t rudder;
    uint16_t elevator;
    uint16_t aileron;
    uint16_t aux1;
    uint16_t aux2;
    uint16_t aux3;
    uint16_t aux4;
};

struct IMUData
{
    Vec3i16 acc;
    Vec3i16 gyro;
};



#endif // TYPES

