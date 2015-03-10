#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "../../Entity/Role/Hero.h"

class GameLayer : public cocos2d::Layer {
public:
    virtual bool init();
    CREATE_FUNC(GameLayer);
    virtual void update(float dt);
    void setPlayer(cocos2d::TMXTiledMap* map, Hero* hero);

private:
    //TODO:
    //void createHPSlider()
};

#endif