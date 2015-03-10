#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"
#include "../../Controller/Controller.h"
#include "RoleFSM.h"

typedef struct _BoundingBox {
    cocos2d::Rect actual;
    cocos2d::Rect original;
} BoundingBox;

class Role : public cocos2d::Node, public ControllerListener {
public:
    Role();
    ~Role();
    cocos2d::Sprite* getSprite();
    void bindSprite(cocos2d::Sprite* sprite);
    void setController(Controller* controller);

    virtual void setTagPosition(int x, int y);
    virtual cocos2d::Point getTagPosition();

    RoleFSM* getFSM();
    virtual void update(float dt);

    void runStandAction();
    void runMoveAction();
    void runAttackAction();
    void runSkillAction();
    void runInjuredAction();
    void runDieAction();

    BoundingBox createBoundingBox(cocos2d::Point origin, cocos2d::Size size);
    void updateBoxes();

protected:
    cocos2d::Sprite* m_sprite;
    Controller* m_controller;
    RoleFSM* m_fsm;

    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_standAction, StandAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_moveAction, MoveAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_attackAction, AttackAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_skillAction, SkillAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_injuredAction, InjuredAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_dieAction, DieAction);

    CC_SYNTHESIZE(bool, m_direction, Direction);
    CC_SYNTHESIZE(BoundingBox, m_bodyBox, BodyBox);
    CC_SYNTHESIZE(BoundingBox, m_hitBox, HitBox);
};

#endif