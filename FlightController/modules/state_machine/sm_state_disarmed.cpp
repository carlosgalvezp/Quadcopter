#include "include/state_machine/sm_state_disarmed.h"

#include "HAL.h"
#include "RC.h"

SM_State_Disarmed::SM_State_Disarmed()
    : ready_to_switch_state_(false)
{
    id_ = STATE_DISARMED;
}

void SM_State_Disarmed::output(const Config& /*config*/, State& /*state*/)
{
    HAL::boardLEDs(0, 1, 0);
}

bool SM_State_Disarmed::conditionArmed_Acro(const Config& config, State& state)
{
    if (RC_isIddle(state.rc.rudder))
    {
        ready_to_switch_state_ = true;
    }

    if (ready_to_switch_state_ && conditionArmed(config, state))
    {
        ready_to_switch_state_ = false;
        return true;
    }
    return false;
}

bool SM_State_Disarmed::conditionArmed(const Config& /*config*/, State& state)
{
    return RC_isAtMin(state.rc.throttle) && RC_isAtMax(state.rc.rudder);
}

