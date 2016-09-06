#include "core/GlobalVariables.h"

namespace GlobalVariables
{
	State state_;
	Config config_;
	StateMachine stateMachine_;
}

State& GlobalVariables::getState()
{
	return state_;
}

Config& GlobalVariables::getConfig()
{
	return config_;
}

StateMachine& GlobalVariables::getStateMachine()
{
	return stateMachine_;
}

void GlobalVariables::init()
{

}

