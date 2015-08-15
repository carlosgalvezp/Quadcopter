#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

// ** This struct is returned by the RC module. Each value represents the stick position in us, 1000-2000
typedef struct 
{
	uint16_t throttle;
	uint16_t rudder;
	uint16_t elevator;
	uint16_t aileron;
	uint16_t aux1;
	uint16_t aux2;
	uint16_t aux3;
	uint16_t aux4;
}RCReadings_t;

#endif