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

		this->connections_[this->nConnections_] = c;
	}
}

void SM_State_PowerOn::output(const Config_t *config, State_t *state)
{
	
}

void SM_State_PassThrough::output(const Config_t *config, State_t *state)
{

}

void SM_State_Disarmed::output(const Config_t *config, State_t *state)
{

}

void SM_State_Armed_Acro::output(const Config_t *config, State_t *state)
{

}

bool SM_State_PowerOn::conditionDisarmed(const Config_t *config, State_t *state)
{
	return false;
}

bool SM_State_PowerOn::conditionPassThrough(const Config_t *config, State_t *state)
{
	return false;
}

bool SM_State_Disarmed::conditionArmed_Acro(const Config_t *config, State_t *state)
{
	return false;
}

bool SM_State_Armed_Acro::conditionDisarmed(const Config_t *config, State_t *state)
{
	return false;
}
//
//// ===================== OUTPUT FUNCTIONS ===============================
//void SM_Outputs::dummyOutput(const Config_t *config, State_t *state)
//{
//}
//
//void SM_Outputs::powerOn(const Config_t *config, State_t *state)
//{
//	HAL::boardLEDs(1, 1, 1);
//}
//
//void SM_Outputs::disarmed(const Config_t *config, State_t *state)
//{
//	// LEDs
//	HAL::boardLEDs(0, 1, 0);
//}
//
//void SM_Outputs::passThrough(const Config_t *config, State_t *state)
//{
//	// LEDs
//	HAL::boardLEDs(1, 0, 1);
//
//	// Motors
//	for (uint8_t i = 0; i < N_MOTORS; ++i)
//	{
//		state->motors[i] = state->rc.throttle;
//	}
//	Output::writePWM(&state->motors[0]);
//}
//
//void SM_Outputs::armedAcro(const Config_t *config, State_t *state)
//{
//	// LEDs
//	HAL::boardLEDs(1, 0, 0);
//
//	// Control
//	Control::computeControlCommands(&state->attitude_rpy, &state->rc, &state->motors[0]);
//
//	// Output
//	Output::writePWM(&state->motors[0]);
//}
//
//// ==================== CONDITIONS ======================================
//namespace SM_Conditions
//{
//	bool disarmedToArmedReady(false);
//}
//bool SM_Conditions::dummyCondition(const State_t *state)
//{
//	return false;
//}
//
//
//bool SM_Conditions::powerOn_Disarmed(const State_t *state)
//{
//	static unsigned long tStart = micros();
//	return (micros() - tStart) > TIME_ON_POWER_CONFIGURATION_US;
//}
//
//bool SM_Conditions::powerOn_PassThrough(const State_t *state)
//{
//	return RC_isAtMax(state->rc.throttle) &&
//		RC_isIddle(state->rc.aileron) &&
//		RC_isIddle(state->rc.elevator) &&
//		RC_isIddle(state->rc.rudder);
//}
//
//bool SM_Conditions::disarmed_Armed(const State_t *state)
//{
//	if (RC_isIddle(state->rc.rudder))
//	{
//		SM_Conditions::disarmedToArmedReady = true;
//	}
//
//	if (SM_Conditions::disarmedToArmedReady && RC_isAtMin(state->rc.throttle) && RC_isAtMax(state->rc.rudder))
//	{
//		SM_Conditions::disarmedToArmedReady = false;
//		return true;
//	}
//	return false;
//}

