#include "utils.h"

void Utils::quaternionToRPY(double q0, double q1, double q2, double q3,
                            double * const roll, double * const pitch, double * const yaw)
{
    *roll = atan2(2.0*(q0*q1 + q2*q3), 1.0 - 2.0*(q1*q1 + q2*q2)) * RAD_TO_DEG;
    *pitch = asin(2.0*(q0*q2 - q3*q1)) * RAD_TO_DEG;
    *yaw = atan2(2.0*(q0*q3 + q1*q2), 1.0 - 2.0*(q2*q2 + q3*q3)) * RAD_TO_DEG;
}

