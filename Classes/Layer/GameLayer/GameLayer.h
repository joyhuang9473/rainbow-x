#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "../../Entity/Role/Hero.h"
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
    void setPlayer(Role* player);
    void bindRoleToMap(Role* role, cocos2d::TMXTiledMap* map);
    void setEnemy(cocos2d::TMXTiledMap* map, Hero* enemy, Hero* target);

    void logic(float dt);

    void initPhysics();
    void setPhysicsBodyForRole(Role* role);
    void updatePhysicsBody(float dt);
    bool collisionDetection(const BoundingBox &bodyBoxA, const BoundingBox &bodyBoxB);
    void updateActionScope(float dt);

    void addBoxBodyForRole(Role* role);
    void updateBoxBody(float dt);
    GroupEnemy* currentGroup();
    void nextGroup();
    void addEnemy();

private:
    Hero* m_player;

    cocos2d::TMXTiledMap* m_map;

    b2World* m_world;
    ContactListener* m_contactListener;
    int numsOfEnemy;
    int enemyGroupCounter;
    bool isMissionComplete;
    bool isInterrupted;
};

#endif