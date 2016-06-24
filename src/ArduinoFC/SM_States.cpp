#include "SM_States.h"

SM_State::SM_State():
nConnections_(0)
{
	this->connections_ = new SM_Connection*[N_MAX_CONNECTIONS_STATE];
}

SM_State::~SM_State()
{
	// Delete connections
	for (uint8_t i = 0; i < N_MAX_CONNECTIONS_STATE; ++i)
	{
		delete this->connections_[i];
	}
	delete[] this->connections_;
}

void SM_State::addConnection(SM_State *toState, SMConditionFnc transitionCondition)
{
	if (this->nConnections_ < N_MAX_CONNECTIONS_STATE)
	{
		SM_Connection *c = new SM_Connection();
		c->fromState = this;
		c->toState = toState;
		c->transitionCondition = transitionCondition;

		this->connections_[this->nConnections_++] = c;
	}
}

// ================================================================================

SM_State_PowerOn::SM_State_PowerOn()	
{
	this->id_ = STATE_POWER_ON;
	this->tStart = micros();
}

SM_State_Disarmed::SM_State_Disarmed()
	: readyToSwitchState(false) 
{
	this->id_ = STATE_DISARMED;
}

SM_State_Armed_Acro::SM_State_Armed_Acro()
	: readyToSwitchState(false) 
{
	this->id_ = STATE_ARMED_ACRO;
}

SM_State_PassThrough::SM_State_PassThrough()	
{
	this->id_ = STATE_PASSTHROUGH;
}
// ================================================================================

void SM_State_PowerOn::output(const Config* config, State* state)
{
	HAL::boardLEDs(1, 1, 1);
}

void SM_State_PassThrough::output(const Config* config, State* state)
{
	// LEDs
	HAL::boardLEDs(1, 1, 0);
	
	// Motors
	for (uint8_t i = 0; i < N_MOTORS; ++i)
	{
		state->motors[i] = state->rc.throttle;
	}
	Output::writePWM(&state->motors[0]);
}

void SM_State_Disarmed::output(const Config* config, State* state)
{
	HAL::boardLEDs(0, 1, 0);
}

void SM_State_Armed_Acro::output(const Config* config, State* state)
{
	// LEDs
	HAL::boardLEDs(1, 0, 0);
	
	// Control
	Control::computeControlCommands(&state->attitude_rpy, &state->rc, &state->motors[0]);
	
	// Output
	Output::writePWM(&state->motors[0]);
}

bool SM_State_PowerOn::conditionAny()
{
	return (micros() - this->tStart) > TIME_ON_POWER_CONFIGURATION_US;
}

bool SM_State_PowerOn::conditionDisarmed(const Config* config, State* state)
{
	return this->conditionAny();
}

bool SM_State_PowerOn::conditionPassThrough(const Config* config, State* state)
{
	return this->conditionAny()			  &&
		   RC_isAtMax(state->rc.throttle) &&
		   RC_isIddle(state->rc.aileron)  &&
		   RC_isIddle(state->rc.elevator) &&
		   RC_isIddle(state->rc.rudder);
}

bool SM_State_Disarmed::conditionArmed_Acro(const Config* config, State* state)
{
	if (RC_isIddle(state->rc.rudder))
	{
		this->readyToSwitchState = true;
	}
	
	if (this->readyToSwitchState && this->conditionArmed(config, state)) 
	{
		this->readyToSwitchState = false;
		return true;
	}
	return false;
}

bool SM_State_Disarmed::conditionArmed(const Config* config, State* state)
{
	return RC_isAtMin(state->rc.throttle) && RC_isAtMax(state->rc.rudder);
}

bool SM_State_Armed_Acro::conditionDisarmed(const Config* config, State* state)
{
	if (RC_isIddle(state->rc.rudder))
	{
		this->readyToSwitchState = true;
	}

	if (this->readyToSwitchState && RC_isAtMin(state->rc.throttle) && RC_isAtMax(state->rc.rudder))
	{
		this->readyToSwitchState = false;
		return true;
	}
	return false;
}