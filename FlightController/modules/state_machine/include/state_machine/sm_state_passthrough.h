#ifndef SM_STATE_PASSTHROUGH_H
#define SM_STATE_PASSTHROUGH_H

#include "state_machine/sm_state.h"

class SM_State_PassThrough : public SM_State
{
public:
    SM_State_PassThrough();
    virtual void output(const Config& config, State& state);
private:
};


#endif // SM_STATE_PASSTHROUGH_H
