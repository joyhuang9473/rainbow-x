#ifndef __STATE_H__
#define __STATE_H__

class Role;

class State {
public:
    enum Situation {
        SITUATION_IDLE,
        SITUATION_BOUND,
        SITUATION_MOVE,
        SITUATION_SKILL,
        SITUATION_INJURED,
        SITUATION_ATTACK,
        SITUATION_DIE
    };

    virtual void execute(Role* role) = 0;
};

#endif