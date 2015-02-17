#ifndef __STATE_H__
#define __STATE_H__

class Role;

class State {
public:
    virtual void execute(Role* role) = 0;
};

#endif