#ifndef __STAND_STATE_H__
#define __STAND_STATE_H__

#include "State.h"

class Role;

class StandState : public State {
public:
    virtual void execute(Role* role);
};

#endif