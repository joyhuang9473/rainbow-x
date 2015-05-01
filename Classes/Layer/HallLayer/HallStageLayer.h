#ifndef __HALL_LAYER_H__
#define __HALL_LAYER_H__

#include "cocos2d.h"
#include "../../Entity/Role/Hero.h"

class HallStageLayer : public cocos2d::Layer {
public:
    virtual bool init();
    
    CREATE_FUNC(HallStageLayer);

    void setPlayer();

    void setStage();

    Hero::HeroType selectRole(cocos2d::Vec2 position);

    std::string selectStage(cocos2d::Vec2 position);
    
    bool isInRange(cocos2d::Vec2 position, cocos2d::Vec2 target_leftBottom, cocos2d::Vec2 target_rightTop);

    virtual void update(float dt);

private:
    cocos2d::TMXTiledMap* m_map;
    Hero* m_player;
    Hero::HeroType m_heroType;
};

#endif
