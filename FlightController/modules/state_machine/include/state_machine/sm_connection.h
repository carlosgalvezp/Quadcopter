#ifndef SM_CONNECTION_H
#define SM_CONNECTION_H

#include "core/Config.h"

class SM_State;
typedef bool(SM_State::*SMConditionFnc)(const Config& config, State& state);

struct SM_Connection
{
    SM_State *fromState;
    SM_State *toState;
    SMConditionFnc transitionCondition;
};

#endif // SM_CONNECTION_H
