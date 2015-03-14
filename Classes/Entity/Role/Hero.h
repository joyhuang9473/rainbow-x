#ifndef __HERO_ENTITY_H__
#define __HERO_ENTITY_H__

#include "cocos2d.h"
#include "Role.h"

class Hero : public Role {
public:
    enum HeroType {
        KISI,
        GNU
    };

    Hero();
    ~Hero();

    bool initWithHeroType(HeroType type);
    static Hero* createWithHeroType(HeroType type);

    void setViewPointByPlayer();
    void setTiledMap(cocos2d::TMXTiledMap* map);
    
    virtual void setTagPosition(int x, int y);

private:
    cocos2d::TMXTiledMap* m_map;
};

#endif