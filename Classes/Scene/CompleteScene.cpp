#include "CompleteScene.h"
#include "../Layer/CompleteLayer/CompleteLayer.h"

bool CompleteScene::init() {
    if ( !Scene::init() ) {
        return false;
    }
    
    this->addChild(CompleteLayer::create());
    return true;
}