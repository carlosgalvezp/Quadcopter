#ifndef MPU6050_H
#define MPU6050_H

#include "I2C.h"
#include "core/Types.h"

#define IMU_DEV_ADDR			0x68

#define IMU_REG_ACC_X_MSB		0x3B
#define IMU_REG_PWR_MGMT_1		0x6B

#define N_BYTES_BURST_READ		14				 // acc(6) + temperature(2) + gyro(6)

#define IMU_REG_GYRO_CONFIG		0x1B
#define IMU_REG_ACCEL_CONFIG	0X1C
#define IMU_REG_INT_PIN_CFG		0x37
#define IMU_REG_WHO_AM_I		0X75

#define ACC_SENSITIVITY			0.00239420166f   // [m/s*s]	   (1/4096) * 9.80665
#define GYRO_SENSITIVITY		0.00000872664f   // [rad/s]    (1/2000) * pi/180

namespace IMU
{
	uint8_t init();
	uint8_t getData(IMUData& data);
}
#endif
