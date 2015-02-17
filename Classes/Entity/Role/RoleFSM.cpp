#include "RoleFSM.h"
#include "../State/State.h"
#include "Role.h"

USING_NS_CC;

RoleFSM* RoleFSM::createWithRole(Role* role) {
    RoleFSM* fsm = new RoleFSM();

    if (fsm && fsm->initWithRole(role)) {
        fsm->autorelease();
    } else {
        CC_SAFE_DELETE(fsm);
        fsm = nullptr;
    }

    return fsm;
}

bool RoleFSM::initWithRole(Role* role) {
    this->m_state = nullptr;
    this->m_role = role;
    this->m_role->retain();

    return true;
}

void RoleFSM::changeState(State* state) {
    CC_SAFE_DELETE(this->m_state);
    this->m_state = state;
}

void RoleFSM::update(float dt) {
    this->m_state->execute(this->m_role);
}

