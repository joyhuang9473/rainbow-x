#ifndef __DIE_SITUATION_H__
#define __DIE_SITUATION_H__

#include "State.h"

class DieSituation : public State {
public:
    virtual void execute(Role* role);
};

#endif