#include "HallStageLayer.h"
#include "../GameLayer/GameManager.h"
#include "../../Scene/GameScene.h"
#include "../../Controller/OperateController.h"

USING_NS_CC;

#define GAMEMANAGER GameManager::getInstance()

bool HallStageLayer::init() {
    if ( !Layer::init() ) {
        return false;
    }

    // Map
    std::vector<std::string> searchPaths;
    searchPaths.push_back("Map");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    this->m_map = TMXTiledMap::create("hall_stage.tmx");
    this->addChild(this->m_map);

    // Hero
    this->m_heroType = Hero::HeroType::NONE;
    this->setPlayer();

    this->scheduleUpdate();
    return true;
}

void HallStageLayer::setPlayer() {
    Vec2 position;

    if (this->m_player == nullptr) {
        TMXObjectGroup* heroObject = this->m_map->getObjectGroup("heroes");
        ValueMap kisi = heroObject->getObject("kisi");
        position.set(kisi["x"].asFloat(), kisi["y"].asFloat());
    } else {
        position = this->m_player->getPosition();
    }

    Hero::HeroType heroType = this->selectRole(position);

    if (heroType == this->m_heroType || heroType == Hero::HeroType::NONE) {
        return;
    }

    this->m_heroType = heroType;

    auto player = Hero::createWithHeroType(heroType);
    player->getFSM()->doEvent("stand");
    player->setTiledMap(this->m_map);
    player->setPosition(position);

    OperateController* operateController = OperateController::create();
    operateController->registerWithKeyboardDispatcher();
    operateController->setRole(player);

    player->setController(operateController);
    player->addChild(operateController);
    player->hideHealthProgress();

    this->removeChild(this->m_player);
    this->m_player = player;
    this->addChild(this->m_player);
}

void HallStageLayer::setStage() {
    if (this->m_player == nullptr) {
        return;
    }

    Vec2 position = this->m_player->getPosition();
    std::string stageFile = this->selectStage(position);
    
    if (stageFile == "") {
        return;
    }
    if (
        this->m_player->getFSM()->getCurrState() == "attacking"
     || this->m_player->getFSM()->getCurrState() == "skilling"
    ) {
        GAMEMANAGER->setCurStageFile(stageFile);
        GAMEMANAGER->setHeroType(this->m_heroType);
        Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, GameScene::create()));

        // Tricky solution
        // TODO
        this->removeChild(this->m_player);
        this->m_player = nullptr;
    }

    return;
}

Hero::HeroType HallStageLayer::selectRole(Vec2 position) {
    TMXObjectGroup* heroObject = this->m_map->getObjectGroup("heroes");
    Size size = Size(64, 64);

    ValueMap kisi = heroObject->getObject("kisi");
    ValueMap kit = heroObject->getObject("kit");
    ValueMap pacman = heroObject->getObject("pacman");
    ValueMap tux = heroObject->getObject("tux");
    ValueMap wilber = heroObject->getObject("wilber");
    ValueMap gnu = heroObject->getObject("gnu");

    if (
        this->isInRange(position,
                        Vec2(kisi["x"].asFloat(), kisi["y"].asFloat()),
                        Vec2(kisi["x"].asFloat() + size.width, kisi["y"].asFloat() + size.height))
    ) {
        return Hero::HeroType::KISI;
    } else if (
        this->isInRange(position,
                        Vec2(gnu["x"].asFloat(), gnu["y"].asFloat()),
                        Vec2(gnu["x"].asFloat() + size.width, gnu["y"].asFloat() + size.height))
    ) {
        return Hero::HeroType::GNU;
    }

    return Hero::HeroType::NONE;
}

std::string HallStageLayer::selectStage(Vec2 position) {
    TMXObjectGroup* stageObject = this->m_map->getObjectGroup("stages");
    ValueMap country_road = stageObject->getObject("country_road");
    ValueMap kingdom_candy = stageObject->getObject("kingdom_candy");
    Size size = Size(128, 128);

    if (
        this->isInRange(position,
                        Vec2(country_road["x"].asFloat(), country_road["y"].asFloat()),
                        Vec2(country_road["x"].asFloat() + size.width, country_road["y"].asFloat() + size.height))
    ) {
        return "country_road.plist";
    } else if (
        this->isInRange(position,
                        Vec2(kingdom_candy["x"].asFloat(), kingdom_candy["y"].asFloat()),
                        Vec2(kingdom_candy["x"].asFloat() + size.width, kingdom_candy["y"].asFloat() + size.height))
    ) {
        return "kindom_candy.plist";
    }

    return "";
}

bool HallStageLayer::isInRange(Vec2 position, Vec2 target_leftBottom, Vec2 target_rightTop) {
    if (
        position.x >= target_leftBottom.x
     && position.x < target_rightTop.x
     && position.y >= target_leftBottom.y
     && position.y < target_rightTop.y
    ) {
        return true;
    } else {
        return false;
    }
}

void HallStageLayer::update(float dt) {
    if (this->m_player == nullptr) {
        return;
    }

    // Action Scope
    Point position = this->m_player->getPosition();
    Size layerSize = this->m_map->getLayer("ground")->getContentSize();
    Size spriteSize = this->m_player->getSprite()->getDisplayFrame()->getRect().size;
    
    position.x = (position.x < layerSize.width - spriteSize.width) ? position.x : layerSize.width - spriteSize.width;
    position.x = (position.x > spriteSize.width) ? position.x : spriteSize.width;
    position.y = (position.y < layerSize.height/2 - spriteSize.height) ? position.y : layerSize.height/2 - spriteSize.height;
    position.y = (position.y > spriteSize.height) ? position.y : spriteSize.height;

    this->m_player->setTagPosition(position.x, position.y);

    // Hero and Stage selection
    TMXObjectGroup* playerObject = this->m_map->getObjectGroup("player");
    ValueMap select_hero = playerObject->getObject("select_hero");

    if (
        this->isInRange(this->m_player->getPosition(),
                        Vec2(0.0, 0.0),
                        Vec2(select_hero["x"].asFloat(), select_hero["y"].asFloat()))
    ) {
        this->setPlayer();
    } else {
        this->setStage();
    }
}

