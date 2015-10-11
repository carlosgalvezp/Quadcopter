#pragma once
#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include "Arduino.h"

#include "RC.h"
#include "StateEstimation.h"
#include "Control.h"
#include "Output.h"
#include "Telemetry.h"

#include "Types.h"
#include "Config.h"

#include "GlobalVariables.h"

#define TIME_ON_POWER_CONFIGURATION_US		1000000  // Time in us after power-on to be able to configure something

namespace MainLoop
{
	void run();

	void armed_run();
	void disarmed_run();

	namespace Utils
	{
		Armed_t disarmedProcessRC();
		Armed_t checkOnPowerConfiguration(const RC_data_t *rc);
		Armed_t checkArming(const State_t * status);

		void changeStatusLEDs(const Armed_t *status);
	}
}

#endif
