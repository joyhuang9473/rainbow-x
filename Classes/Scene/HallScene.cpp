#include "HallScene.h"
#include "../Layer/HallLayer/HallLayer.h"

USING_NS_CC;

bool HallScene::init() {
    if ( !Scene::init() ) {
        return false;
    }

    this->addChild(HallLayer::create());
    return true;
}


