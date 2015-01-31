#include "GameScene.h"
#include "../Layer/GameLayer/MapLayer.h"
#include "../Layer/GameLayer/GameLayer.h"


bool GameScene::init() {
    if ( ! Scene::init() ) {
        return false;
    }

    this->addChild(MapLayer::create(), -1);
    this->addChild(GameLayer::create(), 1);
    return true;
}