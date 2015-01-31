#include "MapLayer.h"

USING_NS_CC;

bool MapLayer::init() {
    if( ! Layer::init() ) {
        return false;
    }

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Sprite* background = Sprite::create("maps/bg_village.jpg");
    Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    
    background->setPosition(Vec2(origin.x + frameSize.width/2, origin.y + frameSize.height/2));
    this->addChild(background, -1);

    return true;
}