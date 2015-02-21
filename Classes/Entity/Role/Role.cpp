#include "Role.h"
#include "RoleFSM.h"

USING_NS_CC;

Role::Role() {
    this->m_sprite = nullptr;
    this->m_fsm = RoleFSM::createWithRole(this);
    this->m_fsm->retain();

    this->m_attackAction = nullptr;
    this->m_dieAction = nullptr;
    this->m_injuredAction = nullptr;
    this->m_moveAction = nullptr;
    this->m_skillAction = nullptr;
    this->m_standAction = nullptr;

    this->scheduleUpdate();
}

Role::~Role() {}

Sprite* Role::getSprite() {
    return this->m_sprite;
}

void Role::bindSprite(Sprite* sprite) {
    this->m_sprite = sprite;
    this->addChild(m_sprite);
}

void Role::setController(Controller* controller) {
    this->m_controller = controller;
    this->m_controller->setControllerListener(this);
}

void Role::setTagPosition(int x, int y) {
    this->setPosition(Vec2(x, y));
}

Point Role::getTagPosition() {
    return this->getPosition();
}

RoleFSM* Role::getFSM() {
    return this->m_fsm;
}

void Role::update(float dt) {
    this->m_fsm->update(dt);
}

void Role::runStandAction() {
    this->m_sprite->runAction(this->m_standAction);
}

void Role::runMoveAction() {
    this->m_sprite->runAction(this->m_moveAction);
}

void Role::runAttackAction() {
    this->m_sprite->runAction(this->m_attackAction);
}

void Role::runSkillAction() {
    this->m_sprite->runAction(this->m_skillAction);
}

void Role::runInjuredAction() {
    this->m_sprite->runAction(this->m_injuredAction);
}

void Role::runDieAction() {
    this->m_sprite->runAction(this->m_dieAction);
}

