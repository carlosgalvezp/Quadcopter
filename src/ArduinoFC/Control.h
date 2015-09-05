#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>

#include "pid.h"
#include "Types.h"

#define CONTROL_U_MIN			1050
#define CONTROL_U_MAX			1950

namespace Control
{
	void computeControlCommands(const vec_float_3_t * const rpy_quad,
								const RC_data_t * const rc_commands,
								uint16_t * const motor_commands);

	void boundControlCommands(uint16_t * const motor_commands);

}
#endif