#include "Role.h"
#include "FSM.h"

USING_NS_CC;

#define FRAMECACHE SpriteFrameCache::getInstance()

Role::Role() {
    this->m_sprite = nullptr;
    this->m_fsm = nullptr;
    this->m_attackAction = nullptr;
    this->m_dieAction = nullptr;
    this->m_injuredAction = nullptr;
    this->m_moveAction = nullptr;
    this->m_skillAction = nullptr;
    this->m_standAction = nullptr;

    this->m_health = 100.0f;
    this->m_maxHealth = 100.0f;
    this->m_attack = 20.0f;

    this->initFSM();
    this->scheduleUpdate();
}

Role::~Role() {}

Sprite* Role::getSprite() {
    return this->m_sprite;
}

void Role::bindSprite(Sprite* sprite) {
    this->m_sprite = sprite;
    this->addChild(m_sprite);

    // set bounding box
    Size spriteSize = this->m_sprite->getDisplayFrame()->getRect().size;
    this->m_bodyBox = this->createBoundingBox(Point(-spriteSize.width/2 - 10, -spriteSize.height / 2), Size(spriteSize.width+25, spriteSize.height));
    this->m_hitBox = this->createBoundingBox(Point(spriteSize.width / 2, -5), Size(25, 20));

    // hp progress bar
    auto size = this->m_sprite->getContentSize();
    this->m_progress = Progress::create();
    this->m_progress->setPosition(size.width*2/3, size.height + this->m_progress->getContentSize().height/2);
    this->addChild(this->m_progress);
}

void Role::setController(Controller* controller) {
    this->m_controller = controller;
    this->m_controller->setControllerListener(this);
}

Controller* Role::getController() {
    return this->m_controller;
}

void Role::setTagPosition(int x, int y) {
    this->setPosition(Vec2(x, y));
    this->updateBoxes();
}

Point Role::getTagPosition() {
    return this->getPosition();
}

void Role::update(float dt) {
    this->m_sprite->setFlippedX(this->getDirection());
}

void Role::initFSM() {
    this->m_fsm = FSM::create("idle");
    this->addChild(this->m_fsm);

    auto onIdle = [this]() {
        this->m_sprite->stopAllActions();

        auto animate = Animate::create(this->m_standAction);
        auto repeat = RepeatForever::create(animate);
        repeat->setTag(AnimationType::IDLE);
        this->m_sprite->runAction(repeat);
    };
    this->m_fsm->setOnEnter("idle", onIdle);

    auto onWalking = [this]() {
        this->m_sprite->stopAllActions();

        auto animate = Animate::create(this->m_moveAction);
        auto repeat = RepeatForever::create(animate);
        repeat->setTag(AnimationType::WALKING);
        this->m_sprite->runAction(repeat);
    };
    this->m_fsm->setOnEnter("walking", onWalking);

    auto onSkilling = [this]() {
        this->m_sprite->stopAllActions();

        auto animate = Animate::create(this->m_skillAction);
        auto callbackFunc = CallFunc::create([this]() {
            this->m_fsm->doEvent("stand");
        });
        auto seq = Sequence::create(animate, callbackFunc, nullptr);
        seq->setTag(AnimationType::SKILLING);
        this->m_sprite->runAction(Speed::create(seq, 3.0f));
    };
    this->m_fsm->setOnEnter("skilling", onSkilling);

    auto onHurting = [this]() {
        this->m_sprite->stopAllActions();

        auto animate = Animate::create(this->m_injuredAction);
        auto callbackFunc = CallFunc::create([this]() {
            this->m_fsm->doEvent("stand");
        });
        auto seq = Sequence::create(DelayTime::create(0.2f), animate, callbackFunc, nullptr);
        seq->setTag(AnimationType::HURTING);
        this->m_sprite->runAction(seq);
    };
    this->m_fsm->setOnEnter("hurting", onHurting);

    auto onAttacking = [this]() {
        this->m_sprite->stopAllActions();

        auto animate = Animate::create(this->m_attackAction);
        auto callbackFunc = CallFunc::create([this]() {
            this->m_fsm->doEvent("stand");
        });
        auto seq = Sequence::create(animate, callbackFunc, nullptr);
        seq->setTag(AnimationType::ATTACKING);
        this->m_sprite->runAction(Speed::create(seq, 3.0f));
    };
    this->m_fsm->setOnEnter("attacking", onAttacking);

    auto onDead = [this]() {
        this->m_sprite->stopAllActions();

        auto animate = Animate::create(this->m_dieAction);
        auto callbackFunc = CallFunc::create([this]() {
            this->m_fsm->doEvent("stand");
        });
        auto seq = Sequence::create(animate, callbackFunc, nullptr);
        seq->setTag(AnimationType::DEAD);
        this->m_sprite->runAction(seq);
    };
    this->m_fsm->setOnEnter("dead", onDead);
}

void Role::beHit(float attack) {
    if (!this->m_fsm->doEvent("hurt")) return;

    this->m_health = this->m_health - attack;
    if (this->m_health < 0) this->m_health = 0;

    this->m_progress->setProgress((float)(this->m_health/this->m_maxHealth)*100);
}

BoundingBox Role::createBoundingBox(Point origin, Size size) {
    BoundingBox boundingBox;
    boundingBox.original.origin= origin;
    boundingBox.original.size= size;
    boundingBox.actual.origin = this->getPosition() + boundingBox.original.origin;
    boundingBox.actual.size= size;
    return boundingBox;
}

void Role::updateBoxes() {
    bool isFlippedX = this->m_sprite->isFlippedX();
    float x_hitBox = 0.0f;

    if (isFlippedX) {
        x_hitBox = this->getPosition().x - this->m_hitBox.original.origin.x - this->m_hitBox.original.size.width;
    } else {
        x_hitBox = this->getPosition().x + this->m_hitBox.original.origin.x;
    }

    this->m_hitBox.actual.origin = Point(x_hitBox, this->getPosition().y + this->m_hitBox.original.origin.y);
    this->m_bodyBox.actual.origin = this->getPosition() + this->m_bodyBox.original.origin;
}
