#include "utils.h"

void Utils::quaternionToRPY(double q0, double q1, double q2, double q3,
                            double * const roll, double * const pitch, double * const yaw)
{
    *roll = atan2(2.0*(q0*q1 + q2*q3), 1.0 - 2.0*(q1*q1 + q2*q2)) * RAD_TO_DEG;
    *pitch = asin(2.0*(q0*q2 - q3*q1)) * RAD_TO_DEG;
    *yaw = atan2(2.0*(q0*q3 + q1*q2), 1.0 - 2.0*(q2*q2 + q3*q3)) * RAD_TO_DEG;
}

void Utils::serializeUint32(uint32_t val, QByteArray &out, std::size_t ptr)
{
    out[ptr]     = (uint8_t)((val >> 24) & 0x000000FF);
    out[ptr + 1] = (uint8_t)((val >> 16) & 0x000000FF);
    out[ptr + 2] = (uint8_t)((val >>  8) & 0x000000FF);
    out[ptr + 3] = (uint8_t)((val      ) & 0x000000FF);
}
