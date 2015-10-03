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
	if (!IMU::getData(&data)){}
	{
		String s = "Acc.x: " + String(data.acc.x) + " Acc.y: " + String(data.acc.y) + String(" Acc.z: ") + String(data.acc.z) + " [m/s^2]";
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

void Test::testTelemetry(State_data_t * const state, Config * const config)
{
	// Get timeStamp
	state->status.timeStamp = micros();

	// Send data
	Telemetry::main(state, config);	
}

void Test::testStateEstimation()
{
	// Read sensor data
	Sensor_data_t sensor_data;
	quaternion_t q;
	vec_float_3_t rpy;
	IMU::getData(&sensor_data.imu);
	
	// Estimate attitude
	StateEstimation::estimateAttitude(&sensor_data, &q, &rpy);

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

void Test::testSonar()
{
	float distance;
	if (Sonar::getDistance(&distance))
	{
		Serial.println("Distance: " + String(distance) + " cm");
	}
	delay(100);
}

void Test::testADC()
{
	uint16_t voltage;
	Adc::Power::readVoltage(&voltage);
	Serial.println("Voltage: " + String(voltage));	
	delay(100);
}
void Test::testWholeSystem(State_data_t * const state, Config * const config)
{
	//Serial.println("----------------------------------------");
	// Get timeStamp
	state->status.timeStamp = micros();

	// RC
	//unsigned long t1 = micros();
	RC::getReadings(&state->rc);
	//Serial.println("RC: " + String(micros() - t1));

	// Get sensor data
	//t1 = micros();
	IMU::getData(&state->sensorData.imu);
	//Serial.println("IMU: " + String(micros() - t1));

	//t1 = micros();
	Magnetometer::getData(&state->sensorData.mag);
	//Serial.println("Magneto: " + String(micros() - t1));

	//t1 = micros();
	Barometer::getData(&state->sensorData.pressure, &state->sensorData.temperature);
	//Serial.println("Baro: " + String(micros() - t1));

	// State estimation
	//t1 = micros();
	StateEstimation::estimateAttitude(&state->sensorData, &state->attitude, &state->attitude_rpy);
	//Serial.println("State estimation: " + String(micros() - t1));

	// Control
	//t1 = micros();
	Control::computeControlCommands(&state->attitude_rpy, &state->rc, &state->motors[0]);
	//Serial.println("Control: " + String(micros() - t1));

	// Output
	//t1 = micros();
	Output::writePWM(&state->motors[0]);
	//Serial.println("Output: " + String(micros() - t1));

	// Send data
	Telemetry::main(state, config);

	// Cycle time
	state->status.cycleTime = (uint16_t)(micros() - state->status.timeStamp);

	// Sleep
	if (state->status.cycleTime < CYCLE_TIME_US)
	{
		delayMicroseconds(CYCLE_TIME_US - state->status.cycleTime);
	}
}

void Test::Unit::testAtan2Full()
{
	// Define x-y limits
	float res = 0.01;
	float x_min = -1, x_max = 1, y_min = x_min, y_max = x_max;

	float x = x_min;
	float y = y_min;

	float maxError = 0;

	while (x <= x_max)
	{
		while (y <= y_max)
		{
			float result = RAD_TO_DEG_F * atan2(y, x);
			float resultFast = Utils::FastMath::atan2(y, x);

			float error = fabs(result - resultFast);
			if (error > maxError)
			{
				maxError = error;
			}
			y += res;
		}
		x += res;
	}

	Serial.println("Atan2 Unit Test. Max error: " + String(maxError) + " deg");
}

void Test::Unit::testAtan2()
{
	unsigned long t1, t2;
	float x = micros();
	delay(rand() % 100);
	float y = micros();

	x = 0.2f;
	y = 0.1f;


	t1 = micros();
	float res = Utils::FastMath::atan2(y, x);
	t2 = micros();
	Serial.println("Fast Math: " + String(t2 - t1) + String(" us"));

	t1 = micros();
	float resOK = RAD_TO_DEG_F * atan2(y, x);
	t2 = micros();
	Serial.println("Standard library: " + String(t2 - t1) + String(" us"));

	//t1 = micros();
	//float resSin = asin(1.0f/(micros()%10));
	//t2 = micros();
	//Serial.println("Standard library sin: " + String(t2 - t1) + String(" us"));

	Serial.println("Result: " + String(res) + " ; Should be: " + String(resOK));
}

void Test::Unit::testQuaternionToRPY()
{
	quaternion_t q;
	vec_float_3_t rpy;

	for (int i = 0; i < 100; ++i)
	{
		q.q0 = 0.1f*(micros() % 10);
		q.q1 = 0.1f*(micros() % 10);
		q.q2 = 0.1f*(micros() % 10);
		q.q3 = 0.1f*(micros() % 10);
		unsigned long t1 = micros();
		Utils::quaternionToRPY(&q, &rpy);
		Serial.println("Q->RPY Conversion time: " + String(micros() - t1));
	}
}

void Test::Unit::testEEPROM()
{
	// Fill memory with numbers
	Serial.println("Writing to EEPROM...");
	for (uint16_t i = 0; i < EEPROM_MAX_SIZE_BYTES; ++i)
	{
		EEPROM::write(i, EEPROM_MAX_SIZE_BYTES - i);
	}
	Serial.println("Finished writing to EEPROM");

	// Read and display it
	for (uint16_t i = 0; i < EEPROM_MAX_SIZE_BYTES; ++i)
	{
		uint8_t val = EEPROM::read(i);
		Serial.println("Value at " + String(i) + ": " + String(val));
		delay(100);
	}
}

void Test::testSoftPWM()
{
	GPIO::getBodyLEDs().run();
}