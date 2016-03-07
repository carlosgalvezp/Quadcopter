#include "MainLoop.h"

namespace MainLoop
{
	State_t* state_ = GlobalVariables::getState();
	Config_t* config_ = GlobalVariables::getConfig();
	StateMachine *stateMachine_ = GlobalVariables::getStateMachine();
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
	state_->status.cycleTime = (uint16_t)(micros() - state_->status.timeStamp);

	// Sleep if necessary
	if (CYCLE_TIME_US > state_->status.cycleTime)
	{
		delayMicroseconds(CYCLE_TIME_US - state_->status.cycleTime);
	}
}

void MainLoop::Internal::updateInternalState(State_t *state)
{
	// Get timeStamp
	state->status.timeStamp = micros();

	// Read battery
	Adc::Power::readVoltage(&state->status.battery.voltage);
	Adc::Power::readCurrent(&state->status.battery.current);

	// RC
	RC::getReadings(&state->rc);

	// Get sensor data
	IMU::getData(&state->sensorData.imu);
	//Magnetometer::getData(&state_->sensorData.mag);
	//Barometer::getData(&state_->sensorData.pressure, &state_->sensorData.temperature);

	// State estimation
	StateEstimation::estimateAttitude(&state->sensorData, &state->attitude, &state->attitude_rpy);
}

void MainLoop::Internal::updateStateMachineState(const Config_t *config, State_t *state)
{
	// Get current state
	SM_State *currentSMState = stateMachine_->getCurrentState();

	// Loop all over possible next states
	for (uint8_t i = 0; i < currentSMState->nConnections_; ++i)
	{
		SM_Connection *c = currentSMState->connections_[i];

		// If the change condition is fulfilled, change state
		if ( (currentSMState->*c->transitionCondition)(config,state))
		{
			stateMachine_->updateState(c->toState);
			break;
		}
	}	
}

void MainLoop::Internal::output(State_t *state, Config_t *config)
{
	// Get current state
	SM_State *currentState = stateMachine_->getCurrentState();

	// Call its output function
	currentState->output(config, state);
}