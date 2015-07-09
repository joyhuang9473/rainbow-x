#include "ConditionLayer.h"
#include "GameManager.h"

USING_NS_CC;

#define GAMEMANAGER GameManager::getInstance()

bool ConditionLayer::init() {
    if(!Layer::init()) {
        return false;
    }

    // Menu
    Vector<MenuItem*> MenuItems;
    auto optionItem = MenuItemImage::create("Buttons/signHangingOption.png",
                                            "Buttons/signHangingOption.png",
                                            CC_CALLBACK_0(ConditionLayer::menuOptionCallback, this));
    
    auto closeItem = MenuItemImage::create("Buttons/signHangingClose.png",
                                           "Buttons/signHangingClose.png",
                                           CC_CALLBACK_1(ConditionLayer::menuCloseCallback, this));

    optionItem->setPosition(Vec2(864, 736));
    closeItem->setPosition(Vec2(928, 736));

    MenuItems.pushBack(optionItem);
    MenuItems.pushBack(closeItem);
    
    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void ConditionLayer::menuOptionCallback() {
    //TODO
    return;
}

void ConditionLayer::menuCloseCallback(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}
