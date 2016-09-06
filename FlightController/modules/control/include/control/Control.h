#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>

#include "control/pid.h"
#include "core/Types.h"
#include "core/Config.h"

#define CONTROL_U_MIN			1050
#define CONTROL_U_MAX			1950

namespace Control
{
	void computeControlCommands(const Vector3<int16_t>& rpy_quad,
								const RCData& rc_commands,
								uint16_t* motor_commands);

	void boundControlCommands(uint16_t* const motor_commands);

}
#endif
