#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "../../Entity/Role/Hero.h"
#include "../../Entity/Role/Enemy.h"
#include "../../Controller/ContactListener.h"
#include "GroupEnemy.h"

class GameLayer : public cocos2d::Layer {
public:
    enum SpriteTag {
        SPRITE_HERO,
        SPRITE_ENEMY
    };

    virtual bool init();
    CREATE_FUNC(GameLayer);
    void setPlayer(cocos2d::TMXTiledMap* map, Hero* hero);
    void setEnemy(cocos2d::TMXTiledMap* map, Enemy* enemy, Hero* target);

    bool collisionDetection(const BoundingBox &hitBox, const BoundingBox &bodyBox);

    void initPhysics();
    void addBoxBodyForRole(Role* role);
    void updateBoxBody(float dt);

    GroupEnemy* currentGroup();
    void nextGroup();

    void logic(float dt);
    void updateActionScope(float dt);

private:
    Hero* m_player;
    b2World* m_world;
    ContactListener* m_contactListener;

    cocos2d::TMXTiledMap* m_map;

    int numsOfEnemy;
    int enemyGroupCounter;
    void addEnemy();

    bool isSuccessful;
};

#endif