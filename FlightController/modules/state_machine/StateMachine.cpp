#include "state_machine/StateMachine.h"

#include "state_machine/sm_state_armedacro.h"
#include "state_machine/sm_state_disarmed.h"
#include "state_machine/sm_state_poweron.h"
#include "state_machine/sm_state_passthrough.h"

StateMachine::StateMachine():
n_states_(0)
{
    init();
}


StateMachine::~StateMachine()
{
	// Delete states
    for (uint8_t iState = 0; iState < N_MAX_STATES; ++iState)
	{
        delete  states_[iState];
	}
}

void StateMachine::init()
{
	// Create and states
    SM_State *state_PowerOn		= new SM_State_PowerOn();			addState(state_PowerOn);
    SM_State *state_PassThrough = new SM_State_PassThrough();		addState(state_PassThrough);
    SM_State *state_Disarmed	= new SM_State_Disarmed();			addState(state_Disarmed);
    SM_State *state_Armed_Acro	= new SM_State_Armed_Acro();		addState(state_Armed_Acro);
	
	// Add connections
	state_PowerOn->addConnection   (state_PassThrough,  static_cast<SMConditionFnc>(&SM_State_PowerOn::conditionPassThrough));
	state_PowerOn->addConnection   (state_Disarmed,	    static_cast<SMConditionFnc>(&SM_State_PowerOn::conditionDisarmed));
	state_Disarmed->addConnection  (state_Armed_Acro,	static_cast<SMConditionFnc>(&SM_State_Disarmed::conditionArmed_Acro));
    state_Armed_Acro->addConnection(state_Disarmed,		static_cast<SMConditionFnc>(&SM_State_Armed_Acro::conditionDisarmed));

	// Set initial state
    current_state_ = state_PowerOn;
}

void StateMachine::addState(SM_State *state)
{
    if (n_states_ < N_MAX_STATES)
	{
        states_[n_states_++] = state;
	}
}
