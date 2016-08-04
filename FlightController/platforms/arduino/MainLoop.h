#pragma once
#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include "Arduino.h"

#include "RC.h"
#include "ADC.h"
#include "StateEstimation.h"
#include "Control.h"
#include "Output.h"
#include "Telemetry.h"

#include "Types.h"
#include "Config.h"
#include "StateMachine.h"

#include "GlobalVariables.h"

namespace MainLoop
{
	void run();

	namespace Internal
	{
		void updateInternalState(State_t *state);
		void updateStateMachineState(const Config_t *config, State_t *state);
		void output(State_t *state, Config_t *config);
	}
}

#endif
