#include "MainLoop.h"

namespace MainLoop
{
	State_t *state_ = GlobalVariables::getState();
	Config_t *config_ = GlobalVariables::getConfig();

	namespace Utils
	{
		bool first_run_(false);
		unsigned long t_start_;
	}

	//					R		G		B
	// Disarmed			
	// Armed
	// Passthrough
	// RC-calibration
	bool status_leds[4][3] = { { 0, 1, 0 },
						       { 1, 0, 0 },
						       { 1, 0, 1 },
							   { 0, 1, 1 }
							 };
}



void MainLoop::run()
{
	// Read RC
	RC::getReadings(&state_->rc);

	switch (state_->status.armed)
	{
		case DISARMED:
			disarmed_run();
			break;

		case PASSTHROUGH:
			break;

		case RC_CALIBRATION:
			break;

		case ARMED:
			armed_run();
			break;
	}
}

void MainLoop::disarmed_run()
{
	// Check on-power configuration
	state_->status.armed = MainLoop::Utils::disarmedProcessRC();

	// Modify LEDs
	MainLoop::Utils::changeStatusLEDs(&state_->status.armed);
}

void MainLoop::armed_run()
{
	//Serial.println("----------------------------------------");
	// Get timeStamp
	state_->status.timeStamp = micros();

	// RC
	//unsigned long t1 = micros();
	//RC::getReadings(&state_->rc);
	state_->status.armed = MainLoop::Utils::checkArming(state_);

	//Serial.println("RC: " + String(micros() - t1));

	// Get sensor data
	//t1 = micros();
	//IMU::getData(&state_->sensorData.imu);
	//Serial.println("IMU: " + String(micros() - t1));

	//t1 = micros();
	//Magnetometer::getData(&state_->sensorData.mag);
	//Serial.println("Magneto: " + String(micros() - t1));

	//t1 = micros();
	//Barometer::getData(&state_->sensorData.pressure, &state_->sensorData.temperature);
	//Serial.println("Baro: " + String(micros() - t1));

	// State estimation
	//t1 = micros();
	//StateEstimation::estimateAttitude(&state_->sensorData, &state_->attitude, &state_->attitude_rpy);
	//Serial.println("State estimation: " + String(micros() - t1));

	// Control
	//t1 = micros();
	//Control::computeControlCommands(&state_->attitude_rpy, &state_->rc, &state_->motors[0]);
	//Serial.println("Control: " + String(micros() - t1));

	// Output
	//t1 = micros();
	//Output::writePWM(&state_->motors[0]);
	//Serial.println("Output: " + String(micros() - t1));

	// Send data
	//Telemetry::main(state_, config_);

	// Cycle time
	//state_->status.cycleTime = (uint16_t)(micros() - state_->status.timeStamp);
}

Armed_t MainLoop::Utils::disarmedProcessRC()
{
	Armed_t outOnPower, outArmed;
	// Check on-power configuration
	outOnPower = MainLoop::Utils::checkOnPowerConfiguration(&state_->rc);
		
	// Check arming sequence
	outArmed= MainLoop::Utils::checkArming(state_);

	// Return
	return outOnPower != DISARMED ? outOnPower : outArmed;
}

Armed_t MainLoop::Utils::checkOnPowerConfiguration(const RC_data_t *rc)
{
	// Check if we still have time
	if (!first_run_)
	{
		first_run_ = true;
		t_start_ = micros();
	}

	if ((micros() - t_start_) <= TIME_ON_POWER_CONFIGURATION_US)
	{
		// Check for pass-through mode (throttle to maximum)
		if (rc->throttle >= RC_MAX_IN)			return PASSTHROUGH;

		// Check for RC-calibration mode (elevator to maximum)
		if (rc->elevator >= RC_MAX_IN)			return RC_CALIBRATION;
	}
	return DISARMED;
}

Armed_t MainLoop::Utils::checkArming(const State_t *state)
{
	// Condition: left stick: down-right; right stick: centered
	bool conditionRC = RC_isAtMin(state->rc.throttle) && RC_isAtMax(state->rc.rudder) &&
					   RC_isIddle(state->rc.aileron)  && RC_isIddle(state->rc.elevator);
	
	// Check depending on current status
	switch (state->status.armed)
	{
		case DISARMED:
			return conditionRC ? ARMED : DISARMED;
			break;
		case ARMED:
			return conditionRC ? DISARMED : ARMED; // TO-DO: add more conditions
			break;
	}
	return DISARMED;
}

void MainLoop::Utils::changeStatusLEDs(const Armed_t *status)
{
	digitalWrite(PIN_LED_RED,   status_leds[*status][0]);
	digitalWrite(PIN_LED_GREEN, status_leds[*status][1]);
	digitalWrite(PIN_LED_BLUE,  status_leds[*status][2]);
}