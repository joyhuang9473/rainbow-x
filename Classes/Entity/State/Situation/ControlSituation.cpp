#include "ControlSituation.h"
#include "../../Role/Role.h"

USING_NS_CC;

ControlSituation::ControlSituation(State::Situation situation) {
    this->m_situation = situation;
    this->m_isMove = false;
    this->m_isAttack = false;
}

void ControlSituation::execute(Role* role) {
    switch (this->m_situation) {
        case State::SITUATION_MOVE:
            if (this->m_isMove) break;

            role->getSprite()->setFlippedX(role->getDirection());
            role->runMoveAction();
            this->m_isMove = true;
            break;
        case State::SITUATION_ATTACK:
            if (this->m_isAttack) break;

            role->runAttackAction();
            this->m_isAttack = true;
            break;
        default:
            break;
    }
}
