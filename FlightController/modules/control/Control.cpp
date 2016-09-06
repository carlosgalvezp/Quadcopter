#include "control/Control.h"
#include "RC.h"

namespace Control
{
	PID controller_roll, controller_pitch, controller_yaw;

	/* Assumptions: rpy_quad has angles in radians
					RC_commands has throttle in microseconds, 
					aileron, elevator and rudder in radians
					motor_commands outputs value in microseconds between [CONTROL_U_MIN, CONTROL_U_MAX]

	*/
	void computeControlCommands(const Vector3<int16_t>& rpy_quad,
							    const RCData& rc_commands,
								uint16_t *motor_commands)
	{
		// Get control commands for roll, pitch and yaw
		uint16_t u_roll  = (uint16_t)controller_roll.computeU(rpy_quad.x,  (rc_commands.aileron -  RC_IDDLE_IN) * TILT_MAX_DEG);
		uint16_t u_pitch = (uint16_t)controller_pitch.computeU(rpy_quad.y, (rc_commands.elevator - RC_IDDLE_IN) * TILT_MAX_DEG);
		uint16_t u_yaw   = (uint16_t)controller_yaw.computeU(rpy_quad.z, rc_commands.rudder);

		// Compute output
		motor_commands[0] = rc_commands.throttle - u_pitch - u_roll + u_yaw;
		motor_commands[1] = rc_commands.throttle - u_pitch + u_roll - u_yaw;
		motor_commands[2] = rc_commands.throttle + u_pitch + u_roll + u_yaw;
		motor_commands[3] = rc_commands.throttle + u_pitch - u_roll - u_yaw;

		// Check for bounds and reduce the throttle
		boundControlCommands(motor_commands);
	}
	
	void boundControlCommands(uint16_t * const motor_commands)
	{
		// Get min and max values
		uint16_t maxU = 0, minU = -1;
		for (uint8_t i = 0; i < 4; ++i)
		{
			if (motor_commands[i] > maxU)	maxU = motor_commands[i];
			if (motor_commands[i] < minU)   minU = motor_commands[i];
		}

		// Reduce throttle if control too large
		if (maxU > CONTROL_U_MAX)
		{
			uint16_t diff = CONTROL_U_MAX - maxU;
			for (uint8_t i = 0; i < 4; ++i)
			{
				motor_commands[i] -= diff;
			}
		}

		// TO-DO: handle min situations. If motor_commands ends up negative, it will 
		// become a huge value!
	}
}
