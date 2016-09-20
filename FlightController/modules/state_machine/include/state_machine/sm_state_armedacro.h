#ifndef SM_STATE_ARMEDACRO_H
#define SM_STATE_ARMEDACRO_H

#include "state_machine/sm_state.h"

class SM_State_Armed_Acro : public SM_State
{
public:
    SM_State_Armed_Acro();
    virtual void output(const Config& config, State& state);
    bool conditionDisarmed(const Config& config, State& state);
private:
    bool ready_to_switch_state_;
};


#endif // SM_STATE_ARMEDACRO_H
