#include "include/state_machine/sm_state.h"

SM_State::SM_State():
    n_connections_(0U),
    connections_()
{
}

SM_State::~SM_State()
{
}

void SM_State::addConnection(SM_State *toState, SMConditionFnc transitionCondition)
{
    if (n_connections_ < N_MAX_CONNECTIONS_STATE)
    {
        SM_Connection& c = connections_[n_connections_];
        c.fromState = this;
        c.toState = toState;
        c.transitionCondition = transitionCondition;

        ++n_connections_;
    }
}
