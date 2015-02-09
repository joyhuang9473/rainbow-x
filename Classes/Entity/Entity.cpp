#include "Entity.h"

USING_NS_CC;

Entity::Entity() {
    this->m_sprite = nullptr;
}

Entity::~Entity() {}

Sprite* Entity::getSprite() {
    return this->m_sprite;
}

void Entity::bindSprite(Sprite* sprite) {
    this->m_sprite = sprite;
    this->addChild(m_sprite);
}

void Entity::setController(Controller* controller) {
    this->m_controller = controller;
    this->m_controller->setControllerListener(this);
}

void Entity::setTagPosition(int x, int y) {
    this->setPosition(Vec2(x, y));
}

Point Entity::getTagPosition() {
    return this->getPosition();
}
