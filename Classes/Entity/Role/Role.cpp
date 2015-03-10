#include "Role.h"
#include "RoleFSM.h"

USING_NS_CC;

Role::Role() {
    this->m_sprite = nullptr;
    this->m_fsm = RoleFSM::create();
    this->m_fsm->setRole(this);

    this->m_attackAction = nullptr;
    this->m_dieAction = nullptr;
    this->m_injuredAction = nullptr;
    this->m_moveAction = nullptr;
    this->m_skillAction = nullptr;
    this->m_standAction = nullptr;

    this->addChild(this->m_fsm);
    this->scheduleUpdate();
}

Role::~Role() {}

Sprite* Role::getSprite() {
    return this->m_sprite;
}

void Role::bindSprite(Sprite* sprite) {
    this->m_sprite = sprite;
    this->addChild(m_sprite);

    // set bounding box
    Size spriteSize = this->m_sprite->getDisplayFrame()->getRect().size;
    this->m_bodyBox = this->createBoundingBox(Point(-spriteSize.width/2 - 10, -spriteSize.height / 2), Size(spriteSize.width+25, spriteSize.height));
    this->m_hitBox = this->createBoundingBox(Point(spriteSize.width / 2, -5), Size(25, 20));
}

void Role::setController(Controller* controller) {
    this->m_controller = controller;
    this->m_controller->setControllerListener(this);
}

void Role::setTagPosition(int x, int y) {
    this->setPosition(Vec2(x, y));
    this->updateBoxes();
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

BoundingBox Role::createBoundingBox(Point origin, Size size)
{
    BoundingBox boundingBox;
    boundingBox.original.origin= origin;
    boundingBox.original.size= size;
    boundingBox.actual.origin = this->getPosition() + boundingBox.original.origin;
    boundingBox.actual.size= size;
    return boundingBox;
}

void Role::updateBoxes() {
    bool isFlippedX = this->m_sprite->isFlippedX();
    float x_hitBox = 0.0f;

    if(isFlippedX) {
        x_hitBox = this->getPosition().x - this->m_hitBox.original.origin.x - this->m_hitBox.original.size.width;
    } else {
        x_hitBox = this->getPosition().x + this->m_hitBox.original.origin.x;
    }

    this->m_hitBox.actual.origin = Point(x_hitBox, this->getPosition().y + this->m_hitBox.original.origin.y);
    this->m_bodyBox.actual.origin = this->getPosition() + this->m_bodyBox.original.origin;
}
