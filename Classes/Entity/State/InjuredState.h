#ifndef __INJURED_STATE_H__
#define __INJURED_STATE_H__

#include "State.h"

class InjuredState : public State {
public:
    virtual void execute(Role* role);
};

#endif