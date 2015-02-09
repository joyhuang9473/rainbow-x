#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "../../Entity/Hero/Hero.h"

class GameLayer : public cocos2d::Layer {
public:
    virtual bool init();
    CREATE_FUNC(GameLayer);
    virtual void update(float dt);
    void addPlayer(cocos2d::TMXTiledMap* map);

private:
    void initBG();
    cocos2d::Sprite* m_bgSprite;
    //TODO:
    //void createHPSlider()
};

#endif