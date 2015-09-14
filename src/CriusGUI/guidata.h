#ifndef GUIDATA_H
#define GUIDATA_H

#include <stdint.h>

#include "types.h"

struct GUIData
{
    GUIData();
    ~GUIData();

    StatusData status;
    bool new_status;

    RCData rc_data;
    bool new_RC;

    IMUData imu_data;
    bool new_IMU_data;

    Quaternion attitude;
    bool new_attitude;

};

#endif // GUIDATA_H
