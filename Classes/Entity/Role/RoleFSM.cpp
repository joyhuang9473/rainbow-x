#include "RoleFSM.h"
#include "Role.h"
#include "../State/State.h"
#include "../State/Situation/StandSituation.h"
#include "../State/Situation/DieSituation.h"
#include "../State/Situation/ControlSituation.h"

USING_NS_CC;

RoleFSM::RoleFSM() {}

RoleFSM::~RoleFSM() {}

bool RoleFSM::init() {
    this->m_state = new StandSituation();
    return true;
}

void RoleFSM::setRole(Role* role) {
    this->m_role = role;
}

void RoleFSM::changeSituation(State::Situation situation) {
    if (this->m_situation == situation) return;

    this->setSituation(situation);
    CC_SAFE_DELETE(this->m_state);

    switch (situation) {
        case State::SITUATION_MOVE:
        case State::SITUATION_SKILL:
        case State::SITUATION_INJURED:
        case State::SITUATION_ATTACK:
            this->m_state = new ControlSituation(situation);
            break;
        case State::SITUATION_IDLE:
        case State::SITUATION_BOUND:
            this->m_state = new StandSituation();
            break;
        case State::SITUATION_DIE:
            this->m_state = new DieSituation();
            break;
        default:
            this->m_state = new StandSituation();
    }
}

void RoleFSM::update(float dt) {
    this->m_state->execute(this->m_role);
}
