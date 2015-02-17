#ifndef __ROLE_FSM_H__
#define __ROLE_FSM_H__

#include "cocos2d.h"

class State;
class Role;

class RoleFSM : public cocos2d::Node {
public:
    static RoleFSM* createWithRole(Role* role);
    bool initWithRole(Role* role);

    virtual void update(float dt);
    void changeState(State* state);

protected:
    State* m_state;
    Role* m_role;
};

#endif