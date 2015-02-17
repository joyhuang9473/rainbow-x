#include "Role.h"
#include "RoleFSM.h"

USING_NS_CC;

Role::Role() {
    this->m_sprite = nullptr;
    this->m_fsm = RoleFSM::createWithRole(this);
    this->m_fsm->retain();
    
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
