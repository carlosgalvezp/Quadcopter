#include "TelemetryRequestFncs.h"

namespace TelemetryRequestFncs
{
	const char *magicWord_ = TELEMETRY_MAGIC_WORD;
}

void TelemetryRequestFncs::requestStatus()
{
	TelemetryRequestFncs::requestCmd(TELEMETRY_CMD_OUT_STATUS);
}

void TelemetryRequestFncs::requestPose()
{
	TelemetryRequestFncs::requestCmd(TELEMETRY_CMD_OUT_ATTITUDE);
}

void TelemetryRequestFncs::requestGPS()
{
	TelemetryRequestFncs::requestCmd(TELEMETRY_CMD_OUT_GPS);
}

void TelemetryRequestFncs::requestCmd(uint8_t cmd)
{
	// Send magic word
	Serial.write(TelemetryRequestFncs::magicWord_[0]);
	Serial.write(TelemetryRequestFncs::magicWord_[1]);

	// Send command
	Serial.write(cmd);
}