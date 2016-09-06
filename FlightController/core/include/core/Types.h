#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

// ** This struct is returned by the RC module. Each value represents the stick position in us, 1000-2000
struct RCData
{
	uint16_t throttle;
	uint16_t rudder;
	uint16_t elevator;
	uint16_t aileron;
	uint16_t aux1;
	uint16_t aux2;
	uint16_t aux3;
	uint16_t aux4;
};

template<class T>
struct Vector3
{
	T x;
	T y;
	T z;
};

struct Quaternion
{
	float q0;
	float q1;
	float q2;
	float q3;
};

struct BatteryData
{
	uint16_t voltage;
	uint16_t current;
};

struct IMUData
{
	Vector3<float> acc;
	Vector3<float> gyro;
	Vector3<int16_t> acc_raw;
	Vector3<int16_t> gyro_raw;
};

struct SensorData
{
	IMUData imu;
	Vector3<float> mag;
	Vector3<int16_t> mag_raw;
	float pressure;
	float temperature;
};

enum FlightMode
{
	STATE_POWER_ON = 0,
	STATE_DISARMED,
	STATE_ARMED_ACRO,
	STATE_PASSTHROUGH,
	FAILSAFE,
	ACRO,
	SELF_LEVEL,
	HEADFREE,
	HOLD_Z,
	HOLD_XYZ,
};


struct Status
{
	uint32_t timestamp;
	uint16_t cycle_time;
	BatteryData battery;
	FlightMode flight_mode;
};

struct State
{
	Status status;
	RCData rc;
	SensorData sensor_data;
	Quaternion attitude;
	Vector3<int16_t> attitude_rpy;
	uint16_t motors[4];	
};

struct PIDParams
{
	float kp;
	float kd;
	float ki;
};

struct GPSData
{
	uint8_t fix;
	uint8_t n_satellites;
	Vector3<int32_t> position_ecef;
	Vector3<int32_t> velocity_ecef;
};

typedef union
{
	float xf;
	uint32_t xu;
}u_float_u32;
#endif