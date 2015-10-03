#include "MainLoop.h"

namespace MainLoop
{
	State_t *state_ = GlobalVariables::getState();
	Config_t *config_ = GlobalVariables::getConfig();
}

void MainLoop::run()
{
	//Serial.println("----------------------------------------");
	// Get timeStamp
	state_->status.timeStamp = micros();

	// RC
	//unsigned long t1 = micros();
	RC::getReadings(&state_->rc);
	//Serial.println("RC: " + String(micros() - t1));

	// Get sensor data
	//t1 = micros();
	IMU::getData(&state_->sensorData.imu);
	//Serial.println("IMU: " + String(micros() - t1));

	//t1 = micros();
	Magnetometer::getData(&state_->sensorData.mag);
	//Serial.println("Magneto: " + String(micros() - t1));

	//t1 = micros();
	Barometer::getData(&state_->sensorData.pressure, &state_->sensorData.temperature);
	//Serial.println("Baro: " + String(micros() - t1));

	// State estimation
	//t1 = micros();
	StateEstimation::estimateAttitude(&state_->sensorData, &state_->attitude, &state_->attitude_rpy);
	//Serial.println("State estimation: " + String(micros() - t1));

	// Control
	//t1 = micros();
	Control::computeControlCommands(&state_->attitude_rpy, &state_->rc, &state_->motors[0]);
	//Serial.println("Control: " + String(micros() - t1));

	// Output
	//t1 = micros();
	Output::writePWM(&state_->motors[0]);
	//Serial.println("Output: " + String(micros() - t1));

	// Send data
	Telemetry::main(state_, config_);

	// Cycle time
	state_->status.cycleTime = (uint16_t)(micros() - state_->status.timeStamp);
}
