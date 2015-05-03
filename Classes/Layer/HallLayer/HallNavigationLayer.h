#ifndef __HALL_NAVIGATION_LAYER_H__
#define __HALL_NAVIGATION_LAYER_H__

#include "cocos2d.h"

class HallNavigationLayer : public cocos2d::Layer {
public:
    virtual bool init();
    
    CREATE_FUNC(HallNavigationLayer);

    void menuOptionCallback();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
private:
    cocos2d::TMXTiledMap* m_map;
};

#endif
