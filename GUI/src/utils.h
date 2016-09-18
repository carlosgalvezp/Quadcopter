#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdint.h>
#include <QByteArray>


#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

#define RAD_TO_DEG  (180.0 / M_PI)

namespace Utils
{
    void quaternionToRPY(double q0, double q1, double q2, double q3,
                         double * const roll, double * const pitch, double * const yaw);

    void serializeFloat(float val, QByteArray &out, unsigned int ptr);
}

#endif // UTILS_H
