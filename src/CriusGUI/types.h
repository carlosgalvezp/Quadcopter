#ifndef TYPES
#define TYPES

#include <stdint.h>
#include <QByteArray>
#include "utils.h"

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

struct PID_Params
{
    float kp;
    float ki;
    float kd;
};

struct Config
{
    PID_Params pid_roll;
    PID_Params pid_pitch;
    PID_Params pid_yaw;

    void serialize(QByteArray &data)
    {
        data.resize(sizeof(Config));

        Utils::serializeFloat(pid_roll.kp, data, 0);
        Utils::serializeFloat(pid_roll.kd, data, 4);
        Utils::serializeFloat(pid_roll.ki, data, 8);

        Utils::serializeFloat(pid_pitch.kp, data, 12);
        Utils::serializeFloat(pid_pitch.kd, data, 16);
        Utils::serializeFloat(pid_pitch.ki, data, 20);

        Utils::serializeFloat(pid_yaw.kp, data, 24);
        Utils::serializeFloat(pid_yaw.kd, data, 28);
        Utils::serializeFloat(pid_yaw.ki, data, 32);
    }
};

typedef union
{
    float xf;
    uint8_t xu[4];
}u_float_char;


#endif // TYPES

