#include "MainLoop.h"

namespace MainLoop
{
	State& state_ = GlobalVariables::getState();
	Config& config_ = GlobalVariables::getConfig();
	StateMachine& stateMachine_ = GlobalVariables::getStateMachine();
}

void MainLoop::run()
{
	// Update internal state from sensor data
	Internal::updateInternalState(state_);

	// Update logical state in the state machine
	Internal::updateStateMachineState(config_, state_);
	
	// Output
	Internal::output(state_, config_);

	// Telemetry
	Telemetry::main(state_, config_);

	// Cycle time
	state_.status.cycle_time = (uint16_t)(micros() - state_.status.timestamp);

	// Sleep if necessary
	if (CYCLE_TIME_US > state_.status.cycle_time)
	{
		delayMicroseconds(CYCLE_TIME_US - state_.status.cycle_time);
	}
}

void MainLoop::Internal::updateInternalState(State& state)
{
	// Get timeStamp
	state.status.timestamp = micros();

	// Read battery
	state.status.battery.voltage = Adc::Power::readVoltage();
	state.status.battery.current = Adc::Power::readCurrent();

	// RC
	RC::getReadings(&state.rc);

	// Get sensor data
	IMU::getData(&state.sensor_data.imu);
	//Magnetometer::getData(&state_->sensorData.mag);
	//Barometer::getData(&state_->sensorData.pressure, &state_->sensorData.temperature);

	// State estimation
	StateEstimation::estimateAttitude(&state.sensor_data, &state.attitude, &state.attitude_rpy);
}

void MainLoop::Internal::updateStateMachineState(const Config& config, State& state)
{
	// Get current state
	SM_State *currentSMState = stateMachine_.getCurrentState();
	
	// Loop all over possible next states
	for (uint8_t i = 0; i < currentSMState->nConnections_; ++i)
	{
		SM_Connection *c = currentSMState->connections_[i];

		// If the change condition is fulfilled, change state
		if ( (currentSMState->*c->transitionCondition)(config,state))
		{
			stateMachine_.updateState(c->toState);
			break;
		}
	}	

	// Update flight mode to display in telemtry
	currentSMState = stateMachine_.getCurrentState();
	state.status.flight_mode = currentSMState->id_;
}

void MainLoop::Internal::output(State& state, Config& config)
{
	// Get current state
	SM_State *currentState = stateMachine_.getCurrentState();

	// Call its output function
	currentState->output(config, state);
}