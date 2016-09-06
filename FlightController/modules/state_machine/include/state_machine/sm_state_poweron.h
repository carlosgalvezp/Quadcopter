#ifndef SM_STATE_POWERON_H
#define SM_STATE_POWERON_H

#include "state_machine/sm_state.h"

class SM_State_PowerOn : public SM_State
{
public:
    SM_State_PowerOn();
    virtual void output(const Config& config, State& state);
    bool conditionPassThrough(const Config& config, State& state);
    bool conditionDisarmed(const Config& config, State& state);
private:
    bool conditionAny();
    unsigned long tStart;
};

#endif // SM_STATE_POWERON_H
