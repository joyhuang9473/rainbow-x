#ifndef __OPERATE_CONTROLLER_H__
#define __OPERATE_CONTROLLER_H__

#include "cocos2d.h"
#include "Controller.h"
#include "../Entity/Role/Role.h"

class OperateController : public Controller {
public:
    CREATE_FUNC(OperateController);
    virtual bool init();
    virtual void update(float dt);

    virtual void registerWithKeyboardDispatcher();
    virtual void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    virtual void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

private:
    CC_SYNTHESIZE_RETAIN(Role*, m_role, Role);
    CC_SYNTHESIZE(int, m_VelocityX, VelocityX);
    CC_SYNTHESIZE(int, m_VelocityY, VelocityY);
};

#endif
