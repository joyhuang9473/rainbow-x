#include "MenuLayer.h"
#include "../../Scene/GameScene.h"

USING_NS_CC;

bool MenuLayer::init() {
    if ( !Layer::init() ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vector<MenuItem*> MenuItems;

    auto startItem = MenuItemImage::create("buttons/StartNormal.png",
                                           "buttons/StartNormal.png",
                                           CC_CALLBACK_0(MenuLayer::menuStartCallback, this));

    auto closeItem = MenuItemImage::create("buttons/CloseNormal.png",
                                           "buttons/CloseSelected.png",
                                           CC_CALLBACK_1(MenuLayer::menuCloseCallback, this));
    
    startItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    MenuItems.pushBack(startItem);
    MenuItems.pushBack(closeItem);

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Aslan-Rainbow-x", "fonts/Marker Felt.ttf", 24);

    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);
    
    return true;
}

void MenuLayer::menuStartCallback() {
    CCLOG("START!");
    
    Director::getInstance()->replaceScene(GameScene::create());
}

void MenuLayer::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
