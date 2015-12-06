#include "StateMachine.h"

StateMachine::StateMachine():
nStates_(0)
{
	this->init();
}


StateMachine::~StateMachine()
{
	// Delete states
	for (uint8_t iState = 0; iState < this->nStates_; ++iState)
	{
		SM_State *state = this->states_[iState];
		delete state;
	}
	delete [] this->states_;
}

void StateMachine::init()
{
	// Allocate memory for pointers to states
	this->states_ = new SM_State*[N_MAX_STATES];

	// Create and states
	SM_State *state_PowerOn		= new SM_State_PowerOn();			this->addState(state_PowerOn);
	SM_State *state_PassThrough = new SM_State_PassThrough();		this->addState(state_PassThrough);
	SM_State *state_Disarmed	= new SM_State_Disarmed();			this->addState(state_Disarmed);
	SM_State *state_Armed_Acro	= new SM_State_Armed_Acro();		this->addState(state_Armed_Acro);
	
	// Add connections
	state_PowerOn->addConnection   (state_PassThrough,  static_cast<SMConditionFnc>(&SM_State_PowerOn::conditionPassThrough));
	state_PowerOn->addConnection   (state_Disarmed,	    static_cast<SMConditionFnc>(&SM_State_PowerOn::conditionDisarmed));
	state_Disarmed->addConnection  (state_Armed_Acro,	static_cast<SMConditionFnc>(&SM_State_Disarmed::conditionArmed_Acro));
	state_Armed_Acro->addConnection(	state_Disarmed,		static_cast<SMConditionFnc>(&SM_State_Armed_Acro::conditionDisarmed));

	// Set initial state
	this->currentState_ = state_PowerOn;
}

void StateMachine::addState(SM_State *state)
{
	if (this->nStates_ < N_MAX_STATES)
	{
		this->states_[this->nStates_++] = state;
	}
}