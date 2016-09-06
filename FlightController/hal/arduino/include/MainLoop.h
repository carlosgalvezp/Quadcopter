#pragma once
#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include "Arduino.h"

#include "RC.h"
#include "ADC.h"
#include "state_estimation/StateEstimation.h"
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
		void updateInternalState(State& state);
		void updateStateMachineState(const Config& config, State& state);
		void output(State& state, Config& config);
	}
}

#endif
