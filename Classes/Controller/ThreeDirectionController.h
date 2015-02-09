#ifndef __THREEDIRECTIONCONTROLLER_H__
#define __THREEDIRECTIONCONTROLLER_H__

#include "cocos2d.h"
#include "Controller.h"

class ThreeDirectionController : public Controller {
public:
    CREATE_FUNC(ThreeDirectionController);
    virtual bool init();
    virtual void update(float dt);

    virtual void registerWithKeyboardDispatcher();
    virtual void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    virtual void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

    void setXSpeed(int speed);
    void setYSpeed(int speed);

private:
    int m_XSpeed;
    int m_YSpeed;
};

#endif
