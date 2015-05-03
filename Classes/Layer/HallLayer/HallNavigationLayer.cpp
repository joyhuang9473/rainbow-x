#include "HallNavigationLayer.h"

USING_NS_CC;


bool HallNavigationLayer::init() {
    if ( !Layer::init() ) {
        return false;
    }

    // Map
    std::vector<std::string> searchPaths;
    searchPaths.push_back("Map");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
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

    // Menu
    TMXObjectGroup* menuObject = this->m_map->getObjectGroup("menu");
    ValueMap option = menuObject->getObject("option");
    ValueMap close = menuObject->getObject("close");
    Vector<MenuItem*> MenuItems;

    auto optionItem = MenuItemImage::create("signHangingOption.png",
                                           "signHangingOption.png",
                                           CC_CALLBACK_0(HallNavigationLayer::menuOptionCallback, this));

    auto closeItem = MenuItemImage::create("signHangingClose.png",
                                           "signHangingClose.png",
                                           CC_CALLBACK_1(HallNavigationLayer::menuCloseCallback, this));
    
    optionItem->setPosition(Vec2(option["x"].asFloat(), option["y"].asFloat()));
    closeItem->setPosition(Vec2(close["x"].asFloat(), close["y"].asFloat()));

    MenuItems.pushBack(optionItem);
    MenuItems.pushBack(closeItem);

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void HallNavigationLayer::menuOptionCallback() {
    // TODO
    return;
}

void HallNavigationLayer::menuCloseCallback(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}

