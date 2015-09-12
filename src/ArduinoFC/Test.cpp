#include "Test.h"

bool armed_ = false;

void Test::testRC()
{
	RC_data_t rc_;

	// Get readings
	RC::getReadings(&rc_);

	// Print
	String s = "Throttle: " + String(rc_.throttle) +
		" Aileron: " + String(rc_.aileron) +
		" Elevator: " + String(rc_.elevator) +
		" Rudder: " + String(rc_.rudder) +
		" AUX1: " + String(rc_.aux1) +
		" AUX2: " + String(rc_.aux2);

	Serial.println(s);
}

void Test::testI2CScan()
{
	for (uint8_t i = 1; i < 128; ++i)
	{
		I2C::startCondition();
		if (!I2C::slaPlusM(i, I2C_MODE_WRITE)) // Found device
		{
			Serial.print("Device found at: 0x");
			Serial.print(i, HEX);
			Serial.print("\n");
		}
		I2C::stopCondition();
	}
}

void Test::testCompass()
{
	// Read magnetometer
	vec_float_3_t dataMag;
	if (!Magnetometer::getData(&dataMag))
	{
		// Compute heading
		float heading = atan2(dataMag.y, dataMag.x) * RAD_TO_DEG;
		String s = String(dataMag.x / 10.0f) + "," + String(dataMag.y / 10.0f) + "," + String(dataMag.z / 10.0f) + " => " + String(heading);
		Serial.println(s);
	}
}

void Test::testSensorRead()
{
	IMU_data_t data;
	if (!IMU::getData(&data))
	{
		String s = "Acc.x: " + String(data.acc.x) + " Acc.y: " + String(data.acc.y) + String(" Acc.z: ") + String(data.acc.z) + " [g]";
		Serial.println(s);
		s = "Gyro.x: " + String(data.gyro.x) + " Gyro.y: " + String(data.gyro.y) + String(" Gyro.z: ") + String(data.acc.z) + " [deg/s]";
		Serial.println(s);
	}
	// Read magnetometer
	vec_float_3_t dataMag;
	if (!Magnetometer::getData(&dataMag))
	{
		String s = "Mag.x: " + String(dataMag.x) + " Mag.y: " + String(dataMag.y) + String(" Mag.z: ") + String(dataMag.z) + " [G]";
		Serial.println(s);
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
	Serial.println("--------------------");
}

void Test::testTelemetry()
{
	State_data_t data_;
	
	data_.timeStamp = micros();

	
	//// Read sensors
	//IMU::getData(&data_.imu);
	

	Telemetry::sendData(&data_);	
}

void Test::testStateEstimation()
{
	// Read sensor data
	Sensor_data_t sensor_data;
	quaternion_t q;
	IMU::getData(&sensor_data.imu);
	
	// Estimate attitude
	StateEstimation::estimateAttitude(&sensor_data, &q);

	// Send over telemetry
	//Telemetry::sendAttitude(&q);	
	//String s = String((int16_t)(10000 * q.q0)) + "," + 
	//	String((int16_t)(10000 * q.q1)) + ", " +
	//	String((int16_t)(10000 * q.q2)) + "," +
	//	String((int16_t)(10000 * q.q3));
	//Serial.println(s);
}

/*
In this test, we read data from RC channel 1 and output that value
to motor M1. Then, we read the value from RC channel 2 and check if it
matches
*/
void Test::testOutput()
{
	
	RC_data_t rc_;
	uint16_t pwm_us[4];
	bool toggled = false;
	// Get readings
	RC::getReadings(&rc_);

	if (rc_.rudder < 1200 && rc_.rudder > 0 && rc_.throttle < 1200 && rc_.throttle > 0)
	{ armed_ = !armed_; 
	toggled = true; 
	digitalWrite(PIN_LED_A, armed_);
	}

	// Assign output value for m1
	pwm_us[0] = armed_?rc_.aileron:500;

	// Output
	Output::writePWM(&(pwm_us[0]));
	
	// Print
	String s = "Throttle: " + String(rc_.throttle) +
		" Aileron: " + String(rc_.aileron) +
		" Elevator: " + String(rc_.elevator) +
		" Rudder: " + String(rc_.rudder) +
		" AUX1: " + String(rc_.aux1) +
		" AUX2: " + String(rc_.aux2);

	Serial.println(s);

	if (toggled) delay(2000);
}

void Test::testWholeSystem()
{
	// Read RC

	// Read sensors

	// State estimation

	// Control commands

	// Output
}