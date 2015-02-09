#include "Hero.h"
#include "../../Util/Animation/AnimationUtil.h"

USING_NS_CC;

Hero::Hero() {
    m_map = nullptr;
}

Hero::~Hero() {
    CC_SAFE_RELEASE(m_map);
}

bool Hero::init() {
    return true;
}

void Hero::run() {
    int numFrame = 6;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

    for (int i = 0 ; i < numFrame ; i++) {
        SpriteFrame* frame = frameCache->getSpriteFrameByName(String::createWithFormat("frame-%d.png", i+1)->getCString());
        frames.pushBack(frame);
    }

    Animation* animation = Animation::createWithSpriteFrames(frames, 0.3);
    Animate* animate = Animate::create(animation);
    RepeatForever* repeat = RepeatForever::create(animate);

    this->m_sprite->runAction(repeat);
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
    Entity::setTagPosition(x, y);
    this->setViewPointByPlayer();
}

void Hero::setTiledMap(cocos2d::TMXTiledMap *map) {
    CC_SAFE_RETAIN(map);
    CC_SAFE_RELEASE(this->m_map);
    this->m_map = map;
}
