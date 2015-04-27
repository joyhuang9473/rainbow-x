#include "Enemy.h"
#include "../../Util/Animation/AnimationUtil.h"

USING_NS_CC;

#define FRAMECACHE SpriteFrameCache::getInstance()

Enemy::Enemy() {
    std::vector<std::string> searchPaths;
    searchPaths.push_back("Characters");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    FRAMECACHE->addSpriteFramesWithFile("hero-kisi.plist", "hero-kisi.png");
    FRAMECACHE->addSpriteFramesWithFile("hero-gnu.plist", "hero-gnu.png");
    this->m_map = nullptr;
}

Enemy::~Enemy() {
    CC_SAFE_RELEASE(m_map);
}

bool Enemy::initWithEnemyType(EnemyType type) {
    std::string spName = "";
    
    switch (type) {
        case EnemyType::KISI:
            spName = "kisi";
            break;
        case EnemyType::GNU:
            spName = "gnu";
            break;
        default:
            break;
    }
    
    // frame
    Sprite* enemySprite = Sprite::createWithSpriteFrame(FRAMECACHE->getSpriteFrameByName(StringUtils::format("%s-idle-1.png", spName.c_str())));
    enemySprite->setScale(1.5);
    this->bindSprite(enemySprite);
    
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

Enemy* Enemy::createWithEnemyType(EnemyType type) {
    Enemy* enemy = new Enemy();
    enemy->initWithEnemyType(type);
    return enemy;
}

void Enemy::setTagPosition(int x, int y) {
    Role::setTagPosition(x, y);
}

void Enemy::setTiledMap(cocos2d::TMXTiledMap *map) {
    this->m_map = map;
}
