#include "ArduinoFC.h"

RC_data_t rc_;

void setup() 
{
	Serial.begin(115200);

	HAL::init();
	//RC::init();
	Serial.println("Finished setup");
}

void loop() 
{
	//// Get readings
	//RC::getReadings(&rc_);

	//// Print
	//String s = "Throttle: " + String(rc_.throttle) +
	//	" Aileron: " + String(rc_.aileron) +
	//	" Elevator: " + String(rc_.elevator) +
	//	" Rudder: " + String(rc_.rudder) +
	//	" AUX1: " + String(rc_.aux1) +
	//	" AUX2: " + String(rc_.aux2);

	//Serial.println(s);

	// Get I2C
	//uint8_t data = 0;
	//I2C::readReg(IMU_DEV_ADDR, IMU_REG_WHO_AM_I, &data, (size_t)(1));
	//Serial.print("Managed to read byte: ");
	//Serial.print(data);
	//Serial.print("\n");

	//for (uint8_t i = 1; i < 128; ++i)
	//{
	//	I2C::startCondition();
	//	if (!I2C::slaPlusM(i, I2C_MODE_WRITE)) // Found device
	//	{
	//		Serial.print("Device found at: 0x");
	//		Serial.print(i, HEX);
	//		Serial.print("\n");
	//	}
	//	I2C::stopCondition();
	//}

	IMU_data_t data;
	if (!IMU::getData(&data))
	{
		String s = "Acc.x: " + String(data.acc.x) + " Acc.y: " + String(data.acc.y) + String(" Acc.z: ") + String(data.acc.z) + " [g]";
		Serial.println(s);
		s = "Gyro.x: " + String(data.gyro.x) + " Gyro.y: " + String(data.gyro.y) + String(" Gyro.z: ") + String(data.acc.z) + " [deg/s]";
		Serial.println(s);
	}
	else
	{
		Serial.println("Fail to read IMU");
	}

	// Read magnetometer
	vec_float_3_t dataMag;
	if (!Magnetometer::getData(&dataMag))
	{
		String s = "Mag.x: " + String(dataMag.x) + " Mag.y: " + String(dataMag.y) + String(" Mag.z: ") + String(dataMag.z) + " [G]";
		Serial.println(s);
	}
	else
	{
		Serial.println("Fail to read Magnetometer");
	}
	// Read barometer
	float pressure, temperature;
	if (!Barometer::getData(&pressure, &temperature))
	{
		String s = "Pressure: " + String(pressure) + " [mbar]";
		Serial.println(s);
		s = "Temperature: " + String(temperature) + " [C]";
		Serial.println(s);
	}
	else
	{
		Serial.println("Fail to read Barometer");
	}
	Serial.println("--------------------");
	delay(1000);
}

