#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"
#include "../../Controller/Controller.h"
#include "RoleFSM.h"

class Role : public cocos2d::Node, public ControllerListener {
public:
    Role();
    ~Role();
    cocos2d::Sprite* getSprite();
    void bindSprite(cocos2d::Sprite* sprite);
    void setController(Controller* controller);

    virtual void setTagPosition(int x, int y);
    virtual cocos2d::Point getTagPosition();

    RoleFSM* getFSM();
    virtual void update(float dt);

    virtual void stand() = 0;
    virtual void move() = 0;
    virtual void attack() = 0;
    virtual void skill() = 0;
    virtual void injured() = 0;
    virtual void die() = 0;

protected:
    cocos2d::Sprite* m_sprite;
    Controller* m_controller;
    RoleFSM* m_fsm;
};

#endif