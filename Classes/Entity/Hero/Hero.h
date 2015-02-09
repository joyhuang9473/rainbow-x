#ifndef __HERO_ENTITY_H__
#define __HERO_ENTITY_H__

#include "cocos2d.h"
#include "../Entity.h"

class Hero : public Entity {
public:
    Hero();
    ~Hero();
    CREATE_FUNC(Hero);
    virtual bool init();
    void run();
    void setViewPointByPlayer();
    void setTiledMap(cocos2d::TMXTiledMap* map);

    virtual void setTagPosition(int x, int y);

private:
    cocos2d::TMXTiledMap* m_map;
};

#endif