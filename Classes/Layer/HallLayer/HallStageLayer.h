#ifndef __HALL_LAYER_H__
#define __HALL_LAYER_H__

#include "cocos2d.h"
#include "../../Entity/Role/Role.h"
#include "../../Entity/Role/Hero.h"

class HallStageLayer : public cocos2d::Layer {
public:
    virtual bool init();
    
    CREATE_FUNC(HallStageLayer);

    void setPlayer(Role* player);

    void setStage();

    Hero::HeroType mapRoleByPos(cocos2d::Vec2 position);

    std::string mapStageByPos(cocos2d::Vec2 position);
    
    bool isInRange(cocos2d::Vec2 position, cocos2d::Vec2 target_leftBottom, cocos2d::Vec2 target_rightTop);

    virtual void update(float dt);

    void changeRole();
    void bindRoleToMap(Role* role, cocos2d::TMXTiledMap* map);

private:
    cocos2d::TMXTiledMap* m_map;
    Hero* m_player;
    Hero::HeroType m_heroType;
};

#endif
