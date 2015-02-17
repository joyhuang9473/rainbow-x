#ifndef __ATTACK_STATE_H__
#define __ATTACK_STATE_H__

#include "State.h"

class AttackState : public State {
public:
    virtual void execute(Role* role);
};

#endif