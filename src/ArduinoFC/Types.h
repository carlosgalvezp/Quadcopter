#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

// ** This struct is returned by the RC module. Each value represents the stick position in us, 1000-2000
typedef struct 
{
	uint16_t throttle;
	uint16_t rudder;
	uint16_t elevator;
	uint16_t aileron;
	uint16_t aux1;
	uint16_t aux2;
	uint16_t aux3;
	uint16_t aux4;
}RC_data_t;

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
}vec_int16_3_t;

typedef struct
{
	float x;
	float y;
	float z;
}vec_float_3_t;

typedef struct
{
	float q0;
	float q1;
	float q2;
	float q3;

}quaternion_t;

typedef struct
{
	vec_float_3_t acc;
	vec_int16_3_t acc_raw;
	vec_float_3_t gyro;
	vec_int16_3_t gyro_raw;
}IMU_data_t;

typedef struct
{
	IMU_data_t imu;
	vec_float_3_t mag;
	vec_int16_3_t mag_raw;
	uint16_t pressure;
}Sensor_data_t;

typedef struct
{
	uint32_t timeStamp;
	uint16_t cycleTime;
}Status_t;

typedef struct
{
	// Status
	Status_t status;

	// RC
	RC_data_t rc;

	// Sensors
	Sensor_data_t sensorData;
	
	// State estimation
	quaternion_t attitude;
	vec_float_3_t attitude_rpy;

	// Control input
	uint16_t motors[4];
	
}State_data_t;

typedef struct
{
	float pid; // TO-DO: complete
}Config_t;
#endif