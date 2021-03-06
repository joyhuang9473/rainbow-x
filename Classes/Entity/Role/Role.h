#ifndef __ROLE_ENTITY_H__
#define __ROLE_ENTITY_H__

#include "cocos2d.h"
#include "../../Controller/Controller.h"
#include "FSM.h"
#include "Progress.h"

typedef struct _BoundingBox {
    cocos2d::Rect actual;
    cocos2d::Rect original;
} BoundingBox;

class Role : public cocos2d::Node, public ControllerListener {
public:
    enum AnimationType {
        IDLE,
        WALKING,
        SKILLING,
        HURTING,
        ATTACKING,
        DEAD
    };
    
    Role();
    ~Role();

    cocos2d::Sprite* getSprite();
    void bindSprite(cocos2d::Sprite* sprite);

    void setController(Controller* controller);
    Controller* getController();

    void setTiledMap(cocos2d::TMXTiledMap* map);
    virtual void setTagPosition(int x, int y);
    virtual cocos2d::Point getTagPosition();

    void initFSM();

    virtual void update(float dt);
    BoundingBox createBoundingBox(cocos2d::Point origin, cocos2d::Size size);
    void updateBoxes();

    void beHit(float attack);
    void showHealthProgress();
    void hideHealthProgress();

protected:
    cocos2d::Sprite* m_sprite;
    cocos2d::TMXTiledMap* m_map;
    Controller* m_controller;

    CC_SYNTHESIZE_RETAIN(FSM*, m_fsm, FSM);

    CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_standAction, StandAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_moveAction, MoveAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_attackAction, AttackAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_skillAction, SkillAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_injuredAction, InjuredAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_dieAction, DieAction);

    CC_SYNTHESIZE(bool, m_direction, Direction);
    CC_SYNTHESIZE(BoundingBox, m_bodyBox, BodyBox);
    CC_SYNTHESIZE(BoundingBox, m_hitBox, HitBox);

    CC_SYNTHESIZE(float, m_health, Health);
    CC_SYNTHESIZE(float, m_maxHealth, MaxHealth);
    CC_SYNTHESIZE(float, m_attack, Attack);
    CC_SYNTHESIZE_RETAIN(Progress*, m_progress, Progress);
};

#endif