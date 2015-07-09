#include "AIController.h"

USING_NS_CC;

bool AIController::init() {
	this->m_role = nullptr;
	this->m_target = nullptr;

	this->setVelocityX(0);
    this->setVelocityY(0);

    this->m_eyeArea = 380;
    this->m_attackArea = 70;
    this->m_moveDirection.x = 0;
    this->m_moveDirection.y = 0;

    this->scheduleUpdate();
    this->schedule(schedule_selector(AIController::updateExecute));
    return true;
}

void AIController::update(float dt) {
    if (this->m_controllerListener == nullptr) {
		log("listener null");
        return;
    }

    Point pos = this->m_controllerListener->getTagPosition();
    pos.x += this->getVelocityX();
    pos.y += this->getVelocityY();
    this->m_controllerListener->setTagPosition(pos.x, pos.y);
}

void AIController::updateExecute(float dt) {
    if (this->m_target == nullptr) {
		log("target null");
        return;
    }

    if (this->m_nextDecisionTime <= 0) {
        this->decide(this->m_target->getTagPosition());
    } else {
        --this->m_nextDecisionTime;
    }
}

void AIController::decide(const cocos2d::Vec2 &target) {
    Vec2 location = this->m_controllerListener->getTagPosition();
    float distance = location.getDistance(target);
    bool isFlippedX = this->m_role->getSprite()->isFlippedX();
    bool isOnTargetLeft = (location.x < target.x) ? true : false;

    if (
        (isFlippedX && isOnTargetLeft)
     || (!isFlippedX && !isOnTargetLeft)
    ) {
        this->m_aiState = (CCRANDOM_0_1() > 0.5f) ? AI_PATROL : AI_IDLE;
    } else {
        if (distance < this->m_eyeArea) {
            this->m_aiState = ((distance < this->m_attackArea) && (fabsf(location.y - target.y) < 30)) ? AI_ATTACK : AI_PURSUIT;
        } else {
            this->m_aiState = (CCRANDOM_0_1() > 0.5f) ? AI_PATROL : AI_IDLE;
        }
    }

    switch (this->m_aiState) {
        case AIState::AI_ATTACK:
        {
            this->setVelocityX(0);
            this->setVelocityY(0);
            this->m_role->getFSM()->doEvent("attack");
            this->m_nextDecisionTime = 80;
            break;
        }
        case AIState::AI_IDLE:
        {
            this->setVelocityX(0);
            this->setVelocityY(0);
            this->m_role->getFSM()->doEvent("stand");
            this->m_nextDecisionTime = 15;
            break;
        }
        case AIState::AI_PATROL:
        {
            this->m_role->getFSM()->doEvent("walk");
            this->m_moveDirection.x = CCRANDOM_MINUS1_1();
            this->m_moveDirection.y = CCRANDOM_MINUS1_1();
            this->m_role->setDirection((this->m_moveDirection.x < 0) ? true : false);

            this->setVelocityX((this->m_moveDirection.x < 0) ? -1 : 1);
            this->setVelocityY((this->m_moveDirection.y < 0) ? -1 : 1);
            this->m_nextDecisionTime = 10;
            break;
        }
        case AIState::AI_PURSUIT:
        {
            this->m_role->getFSM()->doEvent("walk");
            this->m_moveDirection = (target - location).getNormalized();
            this->m_role->setDirection((this->m_moveDirection.x < 0) ? true : false);

            this->setVelocityX((this->m_moveDirection.x < 0) ? -1 : 1);
            this->setVelocityY((this->m_moveDirection.y < 0) ? -1 : 1);
            this->m_nextDecisionTime = 10;
            break;
        }
        default:
            this->m_role->getFSM()->doEvent("stand");
            break;
    }

}

void AIController::execute(const cocos2d::Vec2& target) {
    if (this->m_nextDecisionTime <= 0) {
        this->decide(target);
    } else {
        --this->m_nextDecisionTime;
    }
}

void AIController::setRole(Role* role) {
	this->m_role = role;
}

void AIController::setTarget(Role* role) {
	this->m_target = role;
}

Role* AIController::getRole() {
	return this->m_role;
}

Role* AIController::getTarget() {
	return this->m_target;
}
