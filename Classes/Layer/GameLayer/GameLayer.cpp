#include "GameLayer.h"
#include "../../Entity/Role/Hero.h"
#include "../../Controller/OperateController.h"

USING_NS_CC;

#define FRAMECACHE SpriteFrameCache::getInstance()

bool GameLayer::init() {
    if( ! Layer::init() ) {
        return false;
    }

    // Map
    auto map = TMXTiledMap::create("maps/floor.tmx");

    // Hero
    std::vector<std::string> searchPaths;
    searchPaths.push_back("Characters");
    FileUtils::getInstance()->setSearchPaths(searchPaths);

    FRAMECACHE->addSpriteFramesWithFile("hero-kisi.plist", "hero-kisi.png");

    auto player = Hero::create();
    this->setPlayer(map, player);
    
    this->addChild(map, -1);
    this->addChild(player);

    this->m_player = player;
    return true;
}

void GameLayer::setPlayer(TMXTiledMap* map, Hero* hero) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* heroSprite = Sprite::createWithSpriteFrame(FRAMECACHE->getSpriteFrameByName("kisi-idle-1.png"));
    heroSprite->setScale(1.5);

    hero->bindSprite(heroSprite);
    hero->setTiledMap(map);
    // TODO : tilemap's player_point
    hero->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    OperateController* operateController = OperateController::create();
    operateController->registerWithKeyboardDispatcher();
    operateController->setRole(hero);
    
    hero->setController(operateController);
    hero->addChild(operateController);
}

bool GameLayer::collisionDetection(const BoundingBox &hitBox, const BoundingBox &bodyBox) {
    Rect hitRect = hitBox.actual;
    Rect bodyRect = bodyBox.actual;

    if(hitRect.intersectsRect(bodyRect)) {
        return true;
    }
    return false;
}

void GameLayer::update(float delta) {}
