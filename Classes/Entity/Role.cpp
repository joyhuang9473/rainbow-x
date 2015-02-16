#include "Role.h"

USING_NS_CC;

Role::Role() {
    this->m_sprite = nullptr;
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
