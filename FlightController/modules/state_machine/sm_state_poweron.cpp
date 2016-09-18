#include "include/state_machine/sm_state_poweron.h"

#include "Arduino.h"  // micros() (replace with Time lib)

#include "HAL.h"
#include "RC.h"

#define TIME_ON_POWER_CONFIGURATION_US		1000000  // Time in us after power-on to be able to configure something

SM_State_PowerOn::SM_State_PowerOn()
{
    id_ = STATE_POWER_ON;
    t_start_ = micros();
}

void SM_State_PowerOn::output(const Config& /*config*/, State& /*state*/)
{
    HAL::boardLEDs(1, 1, 1);
}

bool SM_State_PowerOn::conditionAny()
{
    return (micros() - t_start_) > TIME_ON_POWER_CONFIGURATION_US;
}

bool SM_State_PowerOn::conditionDisarmed(const Config& /*config*/, State& /*state*/)
{
    return conditionAny();
}

bool SM_State_PowerOn::conditionPassThrough(const Config& /*config*/, State& state)
{
    return conditionAny()			     &&
           RC_isAtMax(state.rc.throttle) &&
           RC_isIddle(state.rc.aileron)  &&
           RC_isIddle(state.rc.elevator) &&
           RC_isIddle(state.rc.rudder);
}
