#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "Types.h"
#include "Config.h"
#include "state_machine/StateMachine.h"

namespace GlobalVariables
{
	Config& getConfig();
	State& getState();
	StateMachine& getStateMachine();

	void init();
}

#endif
