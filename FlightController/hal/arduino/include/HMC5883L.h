#ifndef HMC5883L_H
#define HMC5883L_H

#include "core/Types.h"
#include "I2C.h"

namespace Magnetometer
{
    const uint8_t kMagnetometerI2CAddr = 0x1EU;

    const uint8_t kMagnetometerRegConfA = 0X00U;
    const uint8_t kMagnetometerRegConfB	= 0X01U;
    const uint8_t kMagnetometerRegMode  = 0X02U;
    const uint8_t kMagnetometerRegData  = 0X03U;

    const uint8_t kMagnetometerNBytesToRead	= 6U; // 2 bytes per axis

    const float kMagnetometerSensitivity = 0.91743119F; // 1000/1090 mGa/LSB

	uint8_t init();
	uint8_t getData(Vector3<float>& data);
}
#endif
