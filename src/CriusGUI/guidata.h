#ifndef GUIDATA_H
#define GUIDATA_H

#include <stdint.h>

#include "types.h"

struct GUIData
{
    GUIData();
    ~GUIData();

    StatusData status;
    RCData rc_data;
    Quaternion attitude;

};

#endif // GUIDATA_H
