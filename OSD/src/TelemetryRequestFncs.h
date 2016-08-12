#pragma once
#ifndef TELEMETRY_REQUESTS_FNCS_H
#define TELEMETRY_REQUESTS_FNCS_H

#include "Arduino.h"

#define TASK_PERIOD_STATUS			13000UL
#define TASK_PERIOD_POSE			17000UL
#define TASK_PERIOD_GPS				23000UL

#define TELEMETRY_MAGIC_WORD				"$F"

// ** COMMANDS **
#define TELEMETRY_CMD_OUT_STATUS			1
#define TELEMETRY_CMD_OUT_GPS				106
#define TELEMETRY_CMD_OUT_ATTITUDE			150


namespace TelemetryRequestFncs
{
	void requestStatus();
	void requestPose();
	void requestGPS();

	void requestCmd(uint8_t cmd);
}
#endif