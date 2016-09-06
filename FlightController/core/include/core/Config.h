#ifndef CONFIG_H
#define CONFIG_H

#define CYCLE_TIME_US	2500		  // Cycle time [us] 
#define TILT_MAX_DEG	45			  // Max tilt angle in either roll and pitch [deg]
#define DEBUG						  // Uncomment this line to enable debug

#include "Types.h"

struct Config
{
	PIDParams pid_roll;
	PIDParams pid_pitch;
	PIDParams pid_yaw;
};

#endif