#ifndef __DIE_STATE_H__
#define __DIE_STATE_H__

#include "State.h"

class DieState : public State {
public:
    virtual void execute(Role* role);
};

#endif