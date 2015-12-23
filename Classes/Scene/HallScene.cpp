#include "HallScene.h"
#include "../Layer/HallLayer/HallStageLayer.h"
#include "../Layer/HallLayer/HallNavigationLayer.h"
#include "../Layer/GameLayer/ConditionLayer.h"

USING_NS_CC;

bool HallScene::init() {
    if ( !Scene::init() ) {
        return false;
    }

    this->addChild(HallNavigationLayer::create());
    this->addChild(HallStageLayer::create());
    this->addChild(ConditionLayer::create());

    return true;
}


