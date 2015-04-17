#include "FailScene.h"
#include "../Layer/FailLayer/FailLayer.h"

bool FailScene::init() {
    if ( !Scene::init() ) {
        return false;
    }
    
    this->addChild(FailLayer::create());
    return true;
}
