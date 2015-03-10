#ifndef __CONTROL_SITUATION_H__
#define __CONTROL_SITUATION_H__

#include "State.h"

class ControlSituation : public State {
public:
    ControlSituation(State::Situation situation);
    ~ControlSituation();
    virtual void execute(Role* role);

private:
    State::Situation m_situation;
    bool m_isMove;
    bool m_isAttack;
};

#endif