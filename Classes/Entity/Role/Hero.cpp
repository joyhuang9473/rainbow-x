#include "Hero.h"
#include "../../Util/Animation/AnimationUtil.h"

USING_NS_CC;

Hero::Hero() {
    this->m_map = nullptr;
}

Hero::~Hero() {
    CC_SAFE_RELEASE(m_map);
}

bool Hero::init() {
    Animation* standAnim = AnimationUtil::createAnimWithFrameName("kisi-idle");
    Animation* moveAnim = AnimationUtil::createAnimWithFrameName("kisi-move");
    Animation* attackAnim = AnimationUtil::createAnimWithFrameName("kisi-attack");
    Animation* skillAnim = AnimationUtil::createAnimWithFrameName("kisi-skill");
    Animation* injuredAnim = AnimationUtil::createAnimWithFrameName("kisi-hurt");
    Animation* dieAnim = AnimationUtil::createAnimWithFrameName("kisi-die");

    this->setStandAction(RepeatForever::create(Animate::create(standAnim)));
    this->setMoveAction(RepeatForever::create(Animate::create(moveAnim)));
    this->setAttackAction(RepeatForever::create(Animate::create(attackAnim)));
    this->setSkillAction(RepeatForever::create(Animate::create(skillAnim)));
    this->setInjuredAction(RepeatForever::create(Animate::create(injuredAnim)));
    this->setDieAction(RepeatForever::create(Animate::create(dieAnim)));

    return true;
}

void Hero::setViewPointByPlayer() {
    if (m_sprite == nullptr) {
        return;
    }

    Layer* parent = (Layer*)this->getParent();

    Size mapTiledNum = this->m_map->getMapSize();
    Size tiledSize = this->m_map->getTileSize();
    Size mapSize = Size::Size(mapTiledNum.width*tiledSize.width,
                              mapTiledNum.height*tiledSize.height);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point spritePos = this->getPosition();

    float x = fmax(spritePos.x, visibleSize.width/2);
    float y = fmax(spritePos.y, visibleSize.height/2);

    x = fmin(x, mapSize.width - visibleSize.width/2);
    y = fmin(y, mapSize.height - visibleSize.height/2);

    Point destPos = Vec2(x, y);
    Point centerPos = Vec2(visibleSize.width/2, visibleSize.height/2);
    Point viewPos = centerPos - destPos;

    parent->setPosition(viewPos);
}

void Hero::setTagPosition(int x, int y) {
    Role::setTagPosition(x, y);
    this->setViewPointByPlayer();
}

void Hero::setTiledMap(cocos2d::TMXTiledMap *map) {
    CC_SAFE_RETAIN(map);
    CC_SAFE_RELEASE(this->m_map);
    this->m_map = map;
}
