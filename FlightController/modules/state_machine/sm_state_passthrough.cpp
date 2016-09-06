#include "include/state_machine/sm_state_passthrough.h"

#include "HAL.h"
#include "Output.h"

SM_State_PassThrough::SM_State_PassThrough()
{
    this->id_ = STATE_PASSTHROUGH;
}

void SM_State_PassThrough::output(const Config& /*config*/, State& state)
{
    // LEDs
    HAL::boardLEDs(1, 1, 0);

    // Motors
    for (uint8_t i = 0; i < N_MOTORS; ++i)
    {
        state.motors[i] = state.rc.throttle;
    }
    Output::writePWM(&state.motors[0]);
}
