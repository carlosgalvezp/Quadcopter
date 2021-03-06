#include "core/Test.h"
#include "core/GlobalVariables.h"

namespace Test
{
	State& state_ = GlobalVariables::getState();
	Config& config_ = GlobalVariables::getConfig();
}

void Test::run()
{
	//Test::testRC();
	//Test::testCompass();
	//Test::testSensorRead();
	//Test::testSonar();
	//Test::testStateEstimation();
	//Test::testTelemetry(state_, config_);
	//Test::testADC();
	Test::testSoftPWM();
	//Test::testOutput();
	//Test::testGPS();
	//Test::Unit::testAtan2();
	//Test::Unit::testAtan2Full();
	//Test::Unit::testQuaternionToRPY();
	//Test::Unit::testEEPROM();
	//Test::Unit::testCos();
	//Test::Unit::testSin();
	//Test::Unit::testAsin();
	//Test::Unit::testAcos();

	//Test::Performance::testSin();
	//Test::Performance::testAsin();
	//delay(100);
}

void Test::testRC()
{
	RCData rc_;

	// Get readings
	RC::getReadings(rc_);

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
	Vector3<float> dataMag;
	if (!Magnetometer::getData(dataMag))
	{
		// Compute heading
		float heading = atan2(dataMag.y, dataMag.x) * RAD_TO_DEG;
		String s = String(dataMag.x / 10.0f) + "," + String(dataMag.y / 10.0f) + "," + String(dataMag.z / 10.0f) + " => " + String(heading);
		Serial.println(s);
	}
}

void Test::testSensorRead()
{
	IMUData data;
	if (!IMU::getData(data)){}
	{
		String s = "Acc.x: " + String(data.acc.x) + " Acc.y: " + String(data.acc.y) + String(" Acc.z: ") + String(data.acc.z) + " [m/s^2]";
		Serial.println(s);
		s = "Gyro.x: " + String(data.gyro.x) + " Gyro.y: " + String(data.gyro.y) + String(" Gyro.z: ") + String(data.acc.z) + " [deg/s]";
		Serial.println(s);
	}
	// Read magnetometer
	Vector3<float> dataMag;
	if (!Magnetometer::getData(dataMag))
	{
		String s = "Mag.x: " + String(dataMag.x) + " Mag.y: " + String(dataMag.y) + String(" Mag.z: ") + String(dataMag.z) + " [G]";
		Serial.println(s);
	}
	// Read barometer
	float pressure, temperature;
	if (!Barometer::getData(pressure, temperature))
	{
		String s = "Pressure: " + String(pressure) + " [mbar]";
		Serial.println(s);
		s = "Temperature: " + String(temperature) + " [C]";
		Serial.println(s);
	}
	Serial.println("--------------------");
}

void Test::testTelemetry(State& state, Config& config)
{
	// Get timeStamp
	state.status.timestamp = micros();

	// Send data
	Telemetry::main(state, config);	
}

void Test::testStateEstimation()
{
	// Read sensor data
	SensorData sensor_data;
	Quaternion q;
	Vector3<int16_t> rpy;
	IMU::getData(sensor_data.imu);
	
	// Estimate attitude
	StateEstimation::estimateAttitude(sensor_data, q, rpy);

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
	
	RCData rc_;
	uint16_t pwm_us[4];
	bool toggled = false;
	// Get readings
	RC::getReadings(rc_);

	//if (rc_.rudder < 1200 && rc_.rudder > 0 && rc_.throttle < 1200 && rc_.throttle > 0)
	//{ armed_ = !armed_; 
	//toggled = true; 
	//digitalWrite(PIN_LED_A, armed_);
	//}

	// Assign output value for m1
	pwm_us[0] = rc_.aileron;

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
	if (Sonar::getDistance(distance))
	{
		Serial.println("Distance: " + String(distance) + " cm");
	}
	delay(100);
}

void Test::testADC()
{
	uint16_t voltage = Adc::Power::readVoltage();
	Serial.println("Voltage: " + String(voltage));	
	delay(100);
}

namespace Test
{
	unsigned long maxDeltaGPS(0);
}
void Test::testGPS()
{
	GPSData gps_data;
	unsigned long t1 = micros();
	if (GPS::getGPSData(gps_data))
	{
		Serial.print("Fix: " + String(gps_data.fix));
		Serial.print("; Pos: ");
		Serial.print(gps_data.position_ecef.x);
		Serial.print(",");
		Serial.print(gps_data.position_ecef.y);
		Serial.print(",");
		Serial.print(gps_data.position_ecef.z);
		Serial.print("; Sat: " + String(gps_data.n_satellites) + "\n");
	}
	unsigned long t2 = micros();
	unsigned long delta = t2 - t1;

	if (delta > maxDeltaGPS)
		maxDeltaGPS = delta;

	//Serial.print(delta);
	//Serial.print("/");
	//Serial.print(maxDeltaGPS);
	//Serial.print("\n");
	delayMicroseconds(2500);
}

void Test::Unit::testAtan2Full()
{
	Serial.println("Testing atan2...");
	// Define x-y limits
	float res = 0.01;	
	float maxError = 0;

	for (float x = -1.0f; x <= 1.0f; x += res)
	{
		for (float y = -1.0f; y <= 1.0f; y += res)
		{
			float result = RAD_TO_DEG_F * atan2(y, x);
			float resultFast = 0.01f * Utils::FastMath::atan2(y, x);

			float error = 100.0f*fabs(result - resultFast);
			if (error > maxError)
			{
				maxError = error;
			}
		}
	}

	Serial.println("Atan2 Unit Test. Max error: " + String(maxError) + " (x 0.01) deg");
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

void Test::Unit::testCos()
{
	Serial.println("Testing cos...");
	uint16_t step = 1;
	int16_t worstAngle=0;
	float maxDelta = -1;
	float delta, x_LUT, x_lib;

	for (int16_t x = -18000; x < 18000; x += step)
	{
		x_LUT = Utils::FastMath::cos(x);
		x_lib = cos(0.01f * x * DEG_TO_RAD);
		delta = fabs(x_LUT - x_lib);

		if (delta > maxDelta)
		{
			worstAngle = x;
			maxDelta = delta;
		}
	}
	Serial.println(String(1000.0f * maxDelta) + "(x 0.0001)," + String(worstAngle));
	delay(1000);
}

void Test::Unit::testSin()
{
	Serial.println("Testing sin...");
	uint16_t step = 1;
	int16_t worstAngle=0;
	float maxDelta = -1.0f;
	float delta, x_LUT, x_lib;

	for (int16_t x = -18000; x < 18000; x += step)
	{
		x_LUT = Utils::FastMath::sin(x);
		x_lib = sin(0.01f * x * DEG_TO_RAD);
		delta = fabs(x_LUT - x_lib);
		if (delta > maxDelta)
		{
			worstAngle = x;
			maxDelta = delta;
		}
	}
	Serial.println("Result:");
	Serial.println(String(1000.0f * maxDelta)+","+String(worstAngle));
	delay(1000);
}

void Test::Unit::testAsin()
{
	Serial.println("Testing asin...");
	float step = 0.01f;
	float worstSin = -2.0f;
	float maxDelta = -1;
	float delta, x_LUT, x_lib;

	for (float x = -1.0f; x < 1.0f; x += step)
	{
		x_LUT = Utils::FastMath::asin(x) * 0.01f;
		x_lib = asin(x) * RAD_TO_DEG_F;
		delta = fabs(x_LUT - x_lib);

		if (delta > maxDelta)
		{
			worstSin = x;
			maxDelta = delta;
			Serial.print("Got: "); Serial.print(x_LUT); Serial.print(" ; Should be: "); Serial.println(x_lib);
		}
	}
	Serial.println(String(maxDelta) + "," + String(worstSin));
	delay(1000);
}

void Test::Unit::testAcos()
{
	Serial.println("Testing acos...");
	float step = 0.01f;
	float worstSin = -2.0f;
	float maxDelta = -1;
	float delta, x_LUT, x_lib;

	for (float x = -1.0f; x < 1.0f; x += step)
	{
		x_LUT = Utils::FastMath::acos(x) * 0.01f;
		x_lib = acos(x) * RAD_TO_DEG_F;
		delta = fabs(x_LUT - x_lib);

		if (delta > maxDelta)
		{
			worstSin = x;
			maxDelta = delta;
			Serial.print("Got: "); Serial.print(x_LUT); Serial.print(" ; Should be: "); Serial.println(x_lib);
		}
	}
	Serial.println(String(maxDelta) + "," + String(worstSin));
	delay(1000);
}

void Test::Unit::testQuaternionToRPY()
{
	Quaternion q;
	Vector3<int16_t> rpy;

	for (int i = 0; i < 100; ++i)
	{
		q.q0 = 0.1f*(micros() % 10);
		q.q1 = 0.1f*(micros() % 10);
		q.q2 = 0.1f*(micros() % 10);
		q.q3 = 0.1f*(micros() % 10);
		unsigned long t1 = micros();
		Utils::quaternionToRPY(q, rpy);
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
	GPIO::getLedRed().blink(250);
	GPIO::getLedBlue().blink(500);
	GPIO::getLedGreen().blink(1000);
}
void Test::Performance::testSin()
{
	Serial.println("Timing sin...");
	unsigned long tStart, tEnd;
	int16_t x = -18000;
	tStart = micros();
	for (; x < 18000; ++x)
	{
		Utils::FastMath::sin(x);
	}
	tEnd = micros();
	Serial.println("Time fast sin: " + String((float)(tEnd - tStart) / 36001)+ " us");

	delay(1000);
}



void Test::Performance::testAsin()
{
	Serial.println("Timing asin...");
	unsigned long tStart, tEnd;
	float x = -1.0f;
	uint8_t nIters = 100;
	tStart = micros();
	for (uint8_t i = 0; i < nIters; ++i)
	{
		Utils::FastMath::asin(x);
		asm("");
	}
	tEnd = micros();
	Serial.println("Time fast asin: " + String((float)(tEnd - tStart) / nIters) + " us");

	delay(1000);
}
