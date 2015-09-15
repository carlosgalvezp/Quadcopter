#ifndef GUIDATA_H
#define GUIDATA_H

#include <stdint.h>

#include "types.h"
#include <vector>

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

    std::vector<uint16_t> motors;
    bool new_motors;

};

#endif // GUIDATA_H
