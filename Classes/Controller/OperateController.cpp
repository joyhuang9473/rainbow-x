#include "OperateController.h"
#include "../Entity/State/State.h"

USING_NS_CC;

bool OperateController::init() {
    this->setVelocityX(0);
    this->setVelocityY(0);
    
    this->scheduleUpdate();
    return true;
}

void OperateController::update(float dt) {
    if (this->m_controllerListener == nullptr) {
        return;
    }

    Point pos = this->m_controllerListener->getTagPosition();
    pos.x += this->getVelocityX();
    pos.y += this->getVelocityY();
    this->m_controllerListener->setTagPosition(pos.x, pos.y);
}

void OperateController::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    switch(keyCode) {
        // Direction
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            this->m_role->setDirection(true);
            this->m_role->getFSM()->doEvent("walk");
            this->setVelocityX(-5);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            this->m_role->setDirection(false);
            this->m_role->getFSM()->doEvent("walk");
            this->setVelocityX(5);
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            this->m_role->getFSM()->doEvent("walk");
            this->setVelocityY(5);
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            this->m_role->getFSM()->doEvent("walk");
            this->setVelocityY(-5);
            break;
        case EventKeyboard::KeyCode::KEY_S:
            this->m_role->getFSM()->doEvent("attack");
            break;
        default:
            break;
    }
}

void OperateController::keyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    switch(keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            this->m_role->getFSM()->doEvent("stand");
            this->setVelocityX(0);
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            this->m_role->getFSM()->doEvent("stand");
            this->setVelocityY(0);
            break;
        default:
            break;
    }
}

void OperateController::registerWithKeyboardDispatcher() {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(OperateController::keyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(OperateController::keyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}