#ifndef SM_STATE_H
#define SM_STATE_H

#include "core/Config.h"

#include "state_machine/sm_connection.h"

#define N_MAX_CONNECTIONS_STATE				5

class SM_State
{
public:
    SM_State();
    virtual void output(const Config& config, State& state) = 0;
    virtual ~SM_State();

    uint8_t nConnections_;
    SM_Connection connections_[N_MAX_CONNECTIONS_STATE];
    FlightMode id_;

    void addConnection(SM_State *toState, SMConditionFnc transitionCondition);
protected:

private:

};

#endif // SM_STATE_H
