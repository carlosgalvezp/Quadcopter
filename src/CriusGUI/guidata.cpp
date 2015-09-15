#include "guidata.h"

GUIData::GUIData():
    new_status(false),
    new_RC(false),
    new_IMU_data(false),
    new_attitude(false),
    new_motors(false)
{
    motors = std::vector<uint16_t>(4);
}

GUIData::~GUIData()
{

}

