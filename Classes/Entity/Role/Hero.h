#ifndef __HERO_ENTITY_H__
#define __HERO_ENTITY_H__

#include "cocos2d.h"
#include "Role.h"

class Hero : public Role {
public:
    enum HeroType {
        KISI,
        GNU,
        WILBER,
        TUX,
        PACMAN,
        KIT,
        NONE
    };

    Hero();
    ~Hero();

    bool initWithHeroType(HeroType type);
    static Hero* createWithHeroType(HeroType type);

    void setViewPointByPlayer();
    
    virtual void setTagPosition(int x, int y);

};

#endif