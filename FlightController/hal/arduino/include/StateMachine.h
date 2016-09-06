#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <stdlib.h> // malloc()

#include "SM_States.h"
#include "Types.h"
#include "Config.h"
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
        return this->currentState_;
    }

    inline void updateState(SM_State *newState)
    {
        this->currentState_ = newState;
    }

private:
	uint8_t nStates_;
    SM_State *states_[N_MAX_STATES];
	SM_State *currentState_;

	void init();
	void addState(SM_State *state);
};
#endif
