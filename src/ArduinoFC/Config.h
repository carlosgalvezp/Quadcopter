#ifndef CONFIG_H
#define CONFIG_H

#define CYCLE_TIME_US	2500		  // Cycle time [us] 
#define TILT_MAX_DEG	45			  // Max tilt angle in either roll and pitch [deg]
#define DEBUG						  // Uncomment this line to enable debug

#include "Types.h"

typedef struct
{
	PID_Params_t pid_roll;
	PID_Params_t pid_pitch;
	PID_Params_t pid_yaw;

}Config_t;

#endif