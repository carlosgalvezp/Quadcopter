#ifndef UTILS_H
#define UTILS_H

#include <math.h>

#define RAD_TO_DEG  (180.0 / M_PI)

namespace Utils
{
    void quaternionToRPY(double q0, double q1, double q2, double q3,
                         double * const roll, double * const pitch, double * const yaw);
}

#endif // UTILS_H
