#ifndef SM_STATE_DISARMED_H
#define SM_STATE_DISARMED_H

#include "state_machine/sm_state.h"

class SM_State_Disarmed : public SM_State
{
public:
    SM_State_Disarmed();
    virtual void output(const Config& config, State& state);
    bool conditionArmed_Acro(const Config& config, State& state);
private:
    bool conditionArmed(const Config& config, State& state);

    bool readyToSwitchState;
};

#endif // SM_STATE_DISARMED_H
