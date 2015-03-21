#ifndef __AI_CONTROLLER_H__
#define __AI_CONTROLLER_H__

#include "cocos2d.h"
#include "Controller.h"
#include "../Entity/Role/Role.h"

class AIController : public Controller {
public:
    enum AIState {
        AI_ATTACK,
        AI_IDLE,
        AI_PATROL,
        AI_PURSUIT
    };

    CREATE_FUNC(AIController);
    virtual bool init();
    virtual void update(float dt);
    void updateExecute(float dt);

    void decide(const cocos2d::Vec2& targetPos);
    void execute(const cocos2d::Vec2& targetPos);

private:
    CC_SYNTHESIZE_RETAIN(Role*, m_role, Role);
    CC_SYNTHESIZE_RETAIN(Role*, m_target, Target);
    CC_SYNTHESIZE(int, m_VelocityX, VelocityX);
    CC_SYNTHESIZE(int, m_VelocityY, VelocityY);

    CC_SYNTHESIZE(cocos2d::Vec2, m_moveDirection, MoveDirection);
    CC_SYNTHESIZE(float, m_eyeArea, EyeArea);
    CC_SYNTHESIZE(float, m_attackArea, AttackArea);
    CC_SYNTHESIZE(AIState, m_aiState, AIState);
    unsigned int m_nextDecisionTime;
};

#endif
