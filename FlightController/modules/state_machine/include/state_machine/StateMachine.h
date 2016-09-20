#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <stdlib.h> // malloc()

#include "state_machine/sm_state.h"
#include "core/Types.h"
#include "core/Config.h"
#include "HAL.h"
#include "RC.h"
#include "Output.h"
#include "control/Control.h"

#define N_MAX_STATES			20

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

    inline SM_State *getCurrentState()
    {
        return current_state_;
    }

    inline void updateState(SM_State *newState)
    {
        current_state_ = newState;
    }

private:
	uint8_t n_states_;
    SM_State *states_[N_MAX_STATES];
	SM_State *current_state_;

	void init();
	void addState(SM_State *state);
};
#endif
