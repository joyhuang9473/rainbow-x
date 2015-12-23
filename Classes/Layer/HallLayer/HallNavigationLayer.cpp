#include "HallNavigationLayer.h"

USING_NS_CC;


bool HallNavigationLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // Map
    this->m_map = TMXTiledMap::create("hall_navigation.tmx");
    this->addChild(this->m_map);

    // TODO
    // Section Map
    TMXObjectGroup* sectionObject = this->m_map->getObjectGroup("sections");
    ValueMap section1 = sectionObject->getObject("section1");
    ValueMap section2 = sectionObject->getObject("section2");
    ValueMap section3 = sectionObject->getObject("section3");
    
    auto sectionItem1 = Sprite::create("houseFit.png");
    auto sectionItem2 = Sprite::create("unknown.png");
    auto sectionItem3 = Sprite::create("unknown.png");
    
    sectionItem1->setPosition(Vec2(section1["x"].asFloat(), section1["y"].asFloat()));
    sectionItem2->setPosition(Vec2(section2["x"].asFloat(), section2["y"].asFloat()));
    sectionItem3->setPosition(Vec2(section3["x"].asFloat(), section3["y"].asFloat()));
    
    this->addChild(sectionItem1);
    this->addChild(sectionItem2);
    this->addChild(sectionItem3);

    return true;
}
