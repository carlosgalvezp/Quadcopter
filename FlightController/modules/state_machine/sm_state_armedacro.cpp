#include "include/state_machine/sm_state_armedacro.h"

#include "HAL.h"
#include "RC.h"
#include "Output.h"
#include "control/Control.h"

SM_State_Armed_Acro::SM_State_Armed_Acro()
    : ready_to_switch_state_(false)
{
    id_ = STATE_ARMED_ACRO;
}

void SM_State_Armed_Acro::output(const Config& /*config*/, State& state)
{
    // LEDs
    HAL::boardLEDs(1, 0, 0);

    // Control
    Control::computeControlCommands(state.attitude_rpy, state.rc, &state.motors[0]);

    // Output
    Output::writePWM(&state.motors[0]);
}

bool SM_State_Armed_Acro::conditionDisarmed(const Config& /*config*/, State& state)
{
    if (RC_isIddle(state.rc.rudder))
    {
        ready_to_switch_state_ = true;
    }

    if (ready_to_switch_state_ && RC_isAtMin(state.rc.throttle) && RC_isAtMax(state.rc.rudder))
    {
        ready_to_switch_state_ = false;
        return true;
    }
    return false;
}
