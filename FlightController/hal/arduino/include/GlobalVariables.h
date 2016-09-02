#pragma once
#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "Types.h"
#include "Config.h"
#include "StateMachine.h"

namespace GlobalVariables
{
	Config& getConfig();
	State& getState();
	StateMachine& getStateMachine();

	void init();
}

#endif
