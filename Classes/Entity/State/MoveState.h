#ifndef __MOVE_STATE_H__
#define __MOVE_STATE_H__

#include "State.h"

class MoveState : public State {
public:
    virtual void execute(Role* role);
};

#endif