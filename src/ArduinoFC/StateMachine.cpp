#include "StateMachine.h"

StateMachine::StateMachine():
nStates_(0)
{
	this->init();
}


StateMachine::~StateMachine()
{
	// Free memory for each state and connection
	for (uint8_t iState = 0; iState < this->nStates_; ++iState)
	{
		SM_State *state = this->states_[iState];

		for (uint8_t iConnection = 0; iConnection < state->nConnections; ++iConnection)
		{
			free(state->connections[iConnection]);
		}

		free(state->connections);
		free(state);
	}

	free(this->states_);
}

void StateMachine::init()
{
	// Allocate memory for pointers to states
	this->states_ = (SM_State **) malloc(N_MAX_STATES * sizeof(SM_State*));
	
	// Create states
	SM_State *state_PowerOn			= this->addState(SM_State_Name::POWER_ON,    3, &SM_Outputs::powerOn);
	SM_State *state_PassThrough		= this->addState(SM_State_Name::PASSTHROUGH, 0, &SM_Outputs::passThrough);
	SM_State *state_Disarmed		= this->addState(SM_State_Name::DISARMED,    1, &SM_Outputs::disarmed);
	SM_State *state_Armed_Acro		= this->addState(SM_State_Name::ARMED_ACRO,  1, &SM_Outputs::dummyOutput);
		
	// Add connections
	this->createConnection(state_PowerOn,		state_PassThrough,	&SM_Conditions::powerOn_PassThrough);
	this->createConnection(state_PowerOn,		state_Disarmed,		&SM_Conditions::powerOn_Disarmed);
	this->createConnection(state_Disarmed,		state_Armed_Acro,	&SM_Conditions::dummyCondition);
	this->createConnection(state_Armed_Acro,		state_Disarmed,		&SM_Conditions::dummyCondition);

	// Set initial state
	this->currentState_ = state_PowerOn;
}

SM_State *StateMachine::addState(SM_State_Name::Type name, uint8_t nConnections, void(*output)(const Config_t *config, State_t *state))
{
	// Allocate memory for state
	SM_State *s = (SM_State *)malloc(sizeof(SM_State));

	// Init fields
	s->name = name;
	s->nConnections = 0; // We will update this number when linking connections and states
	s->output = output;

	// Initialize vector of connections
	s->connections = (SM_Connection **)malloc(nConnections * sizeof(SM_Connection*));

	// Add to the state vector
	this->states_[this->nStates_++] = s;

	// Return
	return s;
}

void StateMachine::createConnection(SM_State *fromState, SM_State *toState, bool(*changeCondition)(const State_t *state))
{
	// Allocate memory for connection
	SM_Connection *c = (SM_Connection *)malloc(sizeof(SM_Connection));

	// Update fields
	c->fromState = fromState;
	c->toState = toState;
	c->condition = changeCondition;

	// Update fromState
	fromState->addConnection(c);
}
//
////void outputArmedAcro()
////{
//
//	// Control
//	//Control::computeControlCommands(&state_->attitude_rpy, &state_->rc, &state_->motors[0]);
//
//	// Output
//	//Output::writePWM(&state_->motors[0]);
////}
//

// ===================== OUTPUT FUNCTIONS ===============================
void SM_Outputs::dummyOutput(const Config_t *config, State_t *state)
{
}

void SM_Outputs::powerOn(const Config_t *config, State_t *state)
{
	HAL::boardLEDs(1, 1, 1);
}

void SM_Outputs::disarmed(const Config_t *config, State_t *state)
{
	HAL::boardLEDs(0, 1, 0);
}

void SM_Outputs::passThrough(const Config_t *config, State_t *state)
{
	HAL::boardLEDs(1, 0, 1);
}

// ==================== CONDITIONS ======================================
namespace SM_Conditions
{
	
}
bool SM_Conditions::dummyCondition(const State_t *state)
{
	return false;
}


bool SM_Conditions::powerOn_Disarmed(const State_t *state)
{
	static unsigned long tStart = micros();
	return (micros() - tStart) > TIME_ON_POWER_CONFIGURATION_US;
}

bool SM_Conditions::powerOn_PassThrough(const State_t *state)
{
	return RC_isAtMax(state->rc.throttle) && 
		   RC_isIddle(state->rc.aileron) &&
		   RC_isIddle(state->rc.elevator) &&
		   RC_isIddle(state->rc.rudder);
}