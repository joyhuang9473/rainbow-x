#include "GameLayer.h"
#include "../../Entity/Role/Hero.h"
#include "../../Controller/OperateController.h"

USING_NS_CC;

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

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("red_hair_boy.plist",
                                                             "red_hair_boy.png");

    this->addChild(map, -1);
    this->addPlayer(map);
    
    return true;
}

void GameLayer::addPlayer(TMXTiledMap* map) {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    Sprite* playerSprite = Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName("frame-1.png"));

    Hero* m_player = Hero::create();

    m_player->bindSprite(playerSprite);
    m_player->setTiledMap(map);

    // TODO : tilemap's player_point
    m_player->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    OperateController* operateController = OperateController::create();
    operateController->registerWithKeyboardDispatcher();
    operateController->setRole(m_player);
    this->addChild(operateController);

    m_player->setController(operateController);
    map->addChild(m_player);
}

void GameLayer::update(float delta) {}

