#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "../../Entity/Role/Hero.h"
#include "../../Entity/Role/Enemy.h"
#include "../../Controller/ContactListener.h"

class GameLayer : public cocos2d::Layer {
public:
    enum SpriteTag {
        SPRITE_HERO,
        SPRITE_ENEMY
    };

    virtual bool init();
    CREATE_FUNC(GameLayer);
    virtual void update(float dt);
    void setPlayer(cocos2d::TMXTiledMap* map, Hero* hero);
    void setEnemy(cocos2d::TMXTiledMap* map, Enemy* enemy, Hero* target);

    bool collisionDetection(const BoundingBox &hitBox, const BoundingBox &bodyBox);

    void initPhysics();
    void addBoxBodyForRole(Role* role);
    void updateBoxBody(float dt);

private:
    Role* m_player;
    b2World* m_world;
    ContactListener* m_contactListener;
    //TODO:
    //void createHPSlider()
};

#endif