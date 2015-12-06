#ifndef _SM_STATES_H_
#define _SM_STATES_H_
#pragma once

#include "Config.h"
#include "Types.h"

#define TIME_ON_POWER_CONFIGURATION_US		1000000  // Time in us after power-on to be able to configure something

#define N_MAX_CONNECTIONS_STATE				5


struct SM_Connection;
class SM_State;
typedef bool(SM_State::*SMConditionFnc)(const Config_t *config, State_t *state);

class SM_State
{
public:
	SM_State();
	virtual void output(const Config_t *config, State_t *state) = 0;
	virtual ~SM_State();
	SM_Connection **connections_;
	uint8_t nConnections_;

	void addConnection(SM_State *toState, SMConditionFnc transitionCondition);
protected:
private:
};

struct SM_Connection
{	
	SM_State *fromState;
	SM_State *toState;
	bool(SM_State::* transitionCondition)(const Config_t *config, State_t *state);
};

// ========================================================================================
// ================================= STATE MACHINE: STATES ================================
// ========================================================================================

// ** Power On
class SM_State_PowerOn : public SM_State
{
public: 
	void output(const Config_t *config, State_t *state);
	bool conditionPassThrough(const Config_t *config, State_t *state);
	bool conditionDisarmed(const Config_t *config, State_t *state);
private:
};

class SM_State_PassThrough : public SM_State
{
public:
	void output(const Config_t *config, State_t *state);
private:
};

class SM_State_RCCalibration : public SM_State
{
public:
	void output(const Config_t *config, State_t *state);
private:
};

class SM_State_Disarmed : public SM_State
{
public:
	void output(const Config_t *config, State_t *state);
	bool conditionArmed_Acro(const Config_t *config, State_t *state);
private:
};

class SM_State_Armed_Acro : public SM_State
{
public:
	void output(const Config_t *config, State_t *state);
	bool conditionDisarmed(const Config_t *config, State_t *state);
private:
};

class SM_State_Armed_SelfLevel : public SM_State
{
public:
	void output(const Config_t *config, State_t *state);
private:
};

class SM_State_Armed_HeadFree : public SM_State
{
public:
	void output(const Config_t *config, State_t *state);
private:
};

class SM_State_Armed_Hold_Z : public SM_State
{
public:
	void output(const Config_t *config, State_t *state);
private:
};

class SM_State_Armed_Hold_XY : public SM_State
{
public:
	void output(const Config_t *config, State_t *state);
private:
};

class SM_State_Armed_Hold_XYZ : public SM_State
{
public:
	void output(const Config_t *config, State_t *state);
private:
};

class SM_State_ReturnHome : public SM_State
{
public:
	void output(const Config_t *config, State_t *state);
private:
};

class SM_State_FailSafe : public SM_State
{
public:
	void output(const Config_t *config, State_t *state);
private:
};

#endif // _SM_STATES_H_