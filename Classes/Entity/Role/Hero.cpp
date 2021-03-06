#include "Hero.h"
#include "../../Util/Animation/AnimationUtil.h"

USING_NS_CC;

#define FRAMECACHE SpriteFrameCache::getInstance()

Hero::Hero() {
    FRAMECACHE->addSpriteFramesWithFile("hero-kisi.plist", "hero-kisi.png");
    FRAMECACHE->addSpriteFramesWithFile("hero-gnu.plist", "hero-gnu.png");
    FRAMECACHE->addSpriteFramesWithFile("hero-wilber.plist", "hero-wilber.png");
    FRAMECACHE->addSpriteFramesWithFile("hero-tux.plist", "hero-tux.png");
    FRAMECACHE->addSpriteFramesWithFile("hero-pacman.plist", "hero-pacman.png");
    FRAMECACHE->addSpriteFramesWithFile("hero-kit.plist", "hero-kit.png");
    this->m_map = nullptr;
}

Hero::~Hero() {
    CC_SAFE_RELEASE(m_map);
}

bool Hero::initWithHeroType(HeroType type) {
    std::string spName = "";

    switch (type) {
        case HeroType::KISI:
            spName = "kisi";
            break;
        case HeroType::GNU:
            spName = "gnu";
            break;
        case HeroType::KIT:
            spName = "kit";
            break;
        case HeroType::PACMAN:
            spName = "pacman";
            break;
        case HeroType::TUX:
            spName = "tux";
            break;
        case HeroType::WILBER:
            spName = "wilber";
            break;
        default:
            break;
    }

    // frame
    Sprite* heroSprite = Sprite::createWithSpriteFrame(FRAMECACHE->getSpriteFrameByName(StringUtils::format("%s-idle-1.png", spName.c_str())));
    heroSprite->setScale(1.5);
    this->bindSprite(heroSprite);

    // animation
    Animation* standAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-idle", spName.c_str()).c_str());
    Animation* moveAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-move", spName.c_str()).c_str());
    Animation* attackAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-attack", spName.c_str()).c_str());
    Animation* skillAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-skill", spName.c_str()).c_str());
    Animation* injuredAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-hurt", spName.c_str()).c_str());
    Animation* dieAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-die", spName.c_str()).c_str());
    
    this->setStandAction(standAnim);
    this->setMoveAction(moveAnim);
    this->setAttackAction(attackAnim);
    this->setSkillAction(skillAnim);
    this->setInjuredAction(injuredAnim);
    this->setDieAction(dieAnim);
    
    return true;
}

Hero* Hero::createWithHeroType(HeroType type) {
    Hero* hero = new Hero();
    hero->initWithHeroType(type);
    return hero;
}

void Hero::setViewPointByPlayer() {
    if (this->m_sprite == nullptr) {
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
