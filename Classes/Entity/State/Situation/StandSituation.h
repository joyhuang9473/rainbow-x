#ifndef __STAND_SITUATION_H__
#define __STAND_SITUATION_H__

#include "../State.h"

class Role;

class StandSituation : public State {
public:
    virtual void execute(Role* role);
};

#endif