#ifndef CONFIG_H
#define CONFIG_H

#define CYCLE_TIME_US	2500		  // Cycle time [us] 
#define TILT_MAX_DEG	45			  // Max tilt angle in either roll and pitch [deg]

typedef struct
{
	float pid_roll[3];
	float pid_pitch[3];
	float pid_yaw[3];
}Config;

#endif