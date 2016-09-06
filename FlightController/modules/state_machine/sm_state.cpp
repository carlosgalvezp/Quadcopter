#include "include/state_machine/sm_state.h"

SM_State::SM_State():
    nConnections_(0U),
    connections_()
{
}

SM_State::~SM_State()
{
}

void SM_State::addConnection(SM_State *toState, SMConditionFnc transitionCondition)
{
    if (this->nConnections_ < N_MAX_CONNECTIONS_STATE)
    {
        SM_Connection& c = connections_[nConnections_];
        c.fromState = this;
        c.toState = toState;
        c.transitionCondition = transitionCondition;

        ++nConnections_;
    }
}
