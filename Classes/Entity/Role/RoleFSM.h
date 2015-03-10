#ifndef __ROLE_FSM_H__
#define __ROLE_FSM_H__

#include "cocos2d.h"
#include "../State/State.h"

class Role;

class RoleFSM : public cocos2d::Node {
public:
    RoleFSM();
    ~RoleFSM();
    CREATE_FUNC(RoleFSM);
    virtual bool init();
    void setRole(Role* role);

    virtual void update(float dt);
    void updateSituation(float dt);

    void changeSituation(State::Situation situation);

protected:
    Role* m_role;
    State* m_state;
    CC_SYNTHESIZE(State::Situation, m_situation, Situation);
};

#endif