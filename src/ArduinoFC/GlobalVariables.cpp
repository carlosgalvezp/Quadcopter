#include "GlobalVariables.h"

namespace GlobalVariables
{
	State_t state_;
	Config_t config_;
}

State_t* GlobalVariables::getState()
{
	return &state_;
}

Config_t* GlobalVariables::getConfig()
{
	return &config_;
}

void GlobalVariables::init()
{
	state_.status.armed = DISARMED;
}

