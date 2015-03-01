#include "ControlSituation.h"
#include "../../Role/Role.h"

USING_NS_CC;

ControlSituation::ControlSituation() {
    this->m_isMove = false;
}

void ControlSituation::execute(Role* role) {
    role->getSprite()->setFlippedX(role->getDirection());

    if (!this->m_isMove) {
        role->runMoveAction();
        this->m_isMove = true;
    }
}
