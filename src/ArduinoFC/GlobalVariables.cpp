#include "GlobalVariables.h"

State_t state_;
Config_t config_;

State_t* GlobalVariables::getState()
{
	return &state_;
}

Config_t* GlobalVariables::getConfig()
{
	return &config_;
}