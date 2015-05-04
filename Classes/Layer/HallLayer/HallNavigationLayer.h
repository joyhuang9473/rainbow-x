#ifndef __HALL_NAVIGATION_LAYER_H__
#define __HALL_NAVIGATION_LAYER_H__

#include "cocos2d.h"

class HallNavigationLayer : public cocos2d::Layer {
public:
    virtual bool init();

    CREATE_FUNC(HallNavigationLayer);

private:
    cocos2d::TMXTiledMap* m_map;
};

#endif
