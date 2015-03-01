#ifndef __CONTROL_SITUATION_H__
#define __CONTROL_SITUATION_H__

#include "State.h"

class ControlSituation : public State {
public:
    ControlSituation();
    ~ControlSituation();
    virtual void execute(Role* role);

private:
    bool m_isMove;
};

#endif