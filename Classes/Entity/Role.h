#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"
#include "../Controller/Controller.h"

class Role : public cocos2d::Node, public ControllerListener {
public:
    Role();
    ~Role();
    cocos2d::Sprite* getSprite();
    void bindSprite(cocos2d::Sprite* sprite);
    void setController(Controller* controller);

    virtual void setTagPosition(int x, int y);
    virtual cocos2d::Point getTagPosition();

protected:
    cocos2d::Sprite* m_sprite;
    Controller* m_controller;
};

#endif