#include "ThreeDirectionController.h"

USING_NS_CC;

bool ThreeDirectionController::init() {
    this->m_XSpeed = 0;
    this->m_YSpeed = 0;

    this->scheduleUpdate();
    return true;
}

void ThreeDirectionController::update(float dt) {
    if (this->m_controllerListener == nullptr) {
        return;
    }
    
    Point pos = this->m_controllerListener->getTagPosition();
    pos.x += m_XSpeed;
    pos.y += m_YSpeed;
    this->m_controllerListener->setTagPosition(pos.x, pos.y);
}

void ThreeDirectionController::setXSpeed(int speed) {
    this->m_XSpeed = speed;
}

void ThreeDirectionController::setYSpeed(int speed) {
    this->m_YSpeed = speed;
}

void ThreeDirectionController::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    Point pos = this->m_controllerListener->getTagPosition();

    switch(keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            this->setXSpeed(-10);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            this->setXSpeed(10);
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            this->setYSpeed(10);
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            this->setYSpeed(-10);
            break;
    }

    this->m_controllerListener->setTagPosition(pos.x, pos.y);
}

void ThreeDirectionController::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {

    switch(keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            this->setXSpeed(0);
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            this->setYSpeed(0);
            break;
    }
}

void ThreeDirectionController::registerWithKeyboardDispatcher() {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(ThreeDirectionController::keyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(ThreeDirectionController::keyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}