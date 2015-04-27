#ifndef __ENEMY_ENTITY_H__
#define __ENEMY_ENTITY_H__

#include "cocos2d.h"
#include "Role.h"

class Enemy : public Role {
public:
    enum EnemyType {
        KISI,
        GNU
    };

    Enemy();
    ~Enemy();
    
    bool initWithEnemyType(EnemyType type);
    static Enemy* createWithEnemyType(EnemyType type);

    void setTiledMap(cocos2d::TMXTiledMap* map);
    virtual void setTagPosition(int x, int y);
    
private:
    cocos2d::TMXTiledMap* m_map;
};

#endif