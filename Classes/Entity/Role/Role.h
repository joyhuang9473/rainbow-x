#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"

class Role : public cocos2d::Node {
public:
    Role();
    
    virtual bool init();
    
    CREATE_FUNC(Role);

    void setControlable(bool b);

    virtual Rect getBoundingBox();

    virtual inline void setArmOffsetX(int x){ m_arm_offsetX = x; }

    virtual inline void setArmOffsetY(int y){ m_arm_offsetY = y; }

protected:
    virtual void update(float delta);

    virtual void update_pos();

public:
    
}