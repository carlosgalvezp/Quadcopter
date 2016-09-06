#ifndef HMC5883L_H
#define HMC5883L_H

#include "core/Types.h"
#include "I2C.h"

#define MAGNETOMETER_DEV_ADDR		0x1E

#define MAGNETOMETER_REG_CONF_A		0X00
#define MAGNETOMETER_REG_CONF_B		0X01
#define MAGNETOMETER_REG_MODE		0X02
#define MAGNETOMETER_REG_DATA		0X03

#define MAGNETOMETER_SENSITIVITY	0.91743119f // 1000/1090 mGa/LSB

#define MAGNETOMETER_N_READ_BYTES	6 // 2 bytes per axis

namespace Magnetometer
{
	uint8_t init();
	uint8_t getData(Vector3<float>& data);
}
#endif
