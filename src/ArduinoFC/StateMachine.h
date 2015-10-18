#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <stdlib.h> // malloc()

#include "Types.h"
#include "Config.h"
#include "HAL.h"
#include "RC.h"

#define N_MAX_STATES			20

#define TIME_ON_POWER_CONFIGURATION_US		1000000  // Time in us after power-on to be able to configure something

namespace SM_State_Name
{
	enum Type
	{
		POWER_ON,
		PASSTHROUGH,
		RC_CALIB,
		DISARMED,
		ARMED_ACRO,
	};
}

struct SM_Connection;
struct SM_State
{
	SM_State_Name::Type name;
	uint8_t nConnections;
	SM_Connection ** connections;
	void(*output)(const Config_t *config, State_t *state);

	void addConnection(SM_Connection *connection)
	{
		this->connections[this->nConnections++] = connection;
	}
};

struct SM_Connection
{
	SM_State *fromState;
	SM_State *toState;
	bool (*condition)(const State_t *state);
};


class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	inline SM_State *getCurrentState() { return this->currentState_; };
	inline void updateState(SM_State *newState)	{ this->currentState_ = newState; };

private:
	uint8_t nStates_;
	SM_State **states_;
	SM_State *currentState_;

	void init();

	SM_State *addState(SM_State_Name::Type name, uint8_t nConnections, void (*output)(const Config_t *config, State_t *state));
	void createConnection(SM_State *fromState, SM_State *toState, bool (*changeCondition)(const State_t *state));

};

// Conditions
namespace SM_Conditions
{
	bool dummyCondition(const State_t *state);

	bool powerOn_Disarmed(const State_t *state);
	bool powerOn_PassThrough(const State_t *state);
}

// Outputs
namespace SM_Outputs
{
	void dummyOutput(const Config_t *config, State_t *state);

	void powerOn(const Config_t *config, State_t *state);
	void disarmed(const Config_t *config, State_t *state);
	void passThrough(const Config_t *config, State_t *state);
}


#endif
