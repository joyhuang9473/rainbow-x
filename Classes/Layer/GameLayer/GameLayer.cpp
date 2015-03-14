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
    auto player = Hero::createWithHeroType(Hero::HeroType::KISI);
    this->setPlayer(map, player);
    
    this->addChild(map, -1);
    this->addChild(player);

    this->m_player = player;
    return true;
}

void GameLayer::setPlayer(TMXTiledMap* map, Hero* hero) {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    hero->setTiledMap(map);
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
