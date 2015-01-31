#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

class GameLayer : public cocos2d::Layer {
public:

    virtual bool init();

    CREATE_FUNC(GameLayer);
};

#endif