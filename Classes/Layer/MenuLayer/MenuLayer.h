#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__
#include "cocos2d.h"
#include "../../Entity/Role/Role.h"

class MenuLayer : public cocos2d::Layer {
public:
    virtual bool init();

    CREATE_FUNC(MenuLayer);

    void menuStartCallback();

    void menuCloseCallback(cocos2d::Ref* pSender);

    void setBackground();

    virtual void update(float dt);

    void menuAboutCallback();
    
private:
    cocos2d::TMXTiledMap* m_map;
    Role* m_conductor;
};

#endif