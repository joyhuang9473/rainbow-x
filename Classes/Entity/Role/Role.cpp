#include "Role.h"
#include "../FSM.h"

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
    this->m_progress->setPosition(0, 3*size.height/4);
    this->addChild(this->m_progress);
}

void Role::setController(Controller* controller) {
    this->m_controller = controller;
    this->m_controller->setControllerListener(this);
}

Controller* Role::getController() {
    return this->m_controller;
}

void Role::setTiledMap(TMXTiledMap* map) {
	this->m_map = map;
}

void Role::setTagPosition(int x, int y) {
    this->setPosition(Vec2(x, y));
    this->updateBoxes();
}

Point Role::getTagPosition() {
    return this->getPosition();
}

void Role::initFSM() {
	/*
	* State
	*/
    this->m_fsm = FSM::create("idle");
	this->m_fsm->addState("walking");
	this->m_fsm->addState("skilling");
	this->m_fsm->addState("hurting");
	this->m_fsm->addState("attacking");
	this->m_fsm->addState("dead");

	/*
	* Enter function
	*/
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
        auto repeat = RepeatForever::create(animate);
        repeat->setTag(AnimationType::IDLE);
        this->m_sprite->runAction(repeat);
    };
    this->m_fsm->setOnEnter("dead", onDead);

	/*
	* Event
	*/
	this->m_fsm->addEvent("walk", "idle", "walking")
		->addEvent("skill", "idle", "skilling")
		->addEvent("skill", "walking", "skilling")
		->addEvent("hurt", "idle", "hurting")
		->addEvent("hurt", "walking", "hurting")
		->addEvent("attack", "idle", "attacking")
		->addEvent("attack", "walking", "attacking")
		->addEvent("die", "idle", "dead")
		->addEvent("die", "walking", "dead")
		->addEvent("die", "skilling", "dead")
		->addEvent("die", "hurting", "dead")
		->addEvent("die", "attacking", "dead")
		->addEvent("stand", "walking", "idle")
		->addEvent("stand", "skilling", "idle")
		->addEvent("stand", "hurting", "idle")
		->addEvent("stand", "attacking", "idle")
		->addEvent("stand", "dead", "idle")
		->addEvent("stand", "idle", "idle");

	this->addChild(this->m_fsm);
}

BoundingBox Role::createBoundingBox(Point origin, Size size) {
    BoundingBox boundingBox;
    boundingBox.original.origin= origin;
    boundingBox.original.size= size;
    boundingBox.actual.origin = this->getPosition() + boundingBox.original.origin;
    boundingBox.actual.size= size;
    return boundingBox;
}

void Role::update(float dt) {
    if (this->m_sprite == nullptr) {
        return;
    }

    this->m_sprite->setFlippedX(this->getDirection());

    if (this->m_health <= 0) {
        this->getFSM()->doEvent("die");
    }
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

void Role::beHit(float attack) {
    if (!this->m_fsm->doEvent("hurt")) return;

    this->m_health = this->m_health - attack;
    if (this->m_health < 0) this->m_health = 0;

    this->m_progress->setProgress((float)(this->m_health/this->m_maxHealth)*100);
}

void Role::showHealthProgress() {
    this->m_progress->setVisible(true);
}

void Role::hideHealthProgress() {
    this->m_progress->setVisible(false);
}
