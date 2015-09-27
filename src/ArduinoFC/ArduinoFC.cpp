#include "ArduinoFC.h"

unsigned long t1, t2;
State_data_t state_;
Config config_;

void setup() 
{
	// Init hardware
	HAL::init();

	// Load configuration
	//EEPROM::loadConfig(&config_);

	config_.pid_roll.kp = 1;
	config_.pid_roll.kd = 2;
	config_.pid_roll.ki = 3;

	config_.pid_pitch.kp = 4;
	config_.pid_pitch.kd = 5;
	config_.pid_pitch.ki = 6;

	config_.pid_yaw.kp = 7;
	config_.pid_yaw.kd = 8;
	config_.pid_yaw.ki = 9;
}

void loop() 
{
	//Test::testRC();
	//Test::testCompass();
	//Test::testSensorRead();
	//Test::testSonar();
	//Test::testStateEstimation();
	Test::testTelemetry(&state_, &config_);
	//Test::testOutput();
	//Test::testWholeSystem(&state_);
	//Test::Unit::testAtan2();
	//Test::Unit::testAtan2Full();
	//Test::Unit::testQuaternionToRPY();
	//Test::Unit::testEEPROM();
	delay(10);
}
