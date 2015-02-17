#ifndef __SKILL_STATE_H__
#define __SKILL_STATE_H__

#include "State.h"

class SkillState : public State {
public:
    virtual void execute(Role* role);
};

#endif