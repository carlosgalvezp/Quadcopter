#include "GlobalVariables.h"

namespace GlobalVariables
{
	State_t state_;
	Config_t config_;
	StateMachine stateMachine_;
}

State_t* GlobalVariables::getState()
{
	return &state_;
}

Config_t* GlobalVariables::getConfig()
{
	return &config_;
}

StateMachine* GlobalVariables::getStateMachine()
{
	return &stateMachine_;
}

void GlobalVariables::init()
{

}

