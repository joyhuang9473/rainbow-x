#include "HallLayer.h"
#include "../GameLayer/GameManager.h"
#include "../../Scene/MenuScene.h"
#include "../../Scene/GameScene.h"

USING_NS_CC;

#define GAMEMANAGER GameManager::getInstance()

bool HallLayer::init() {
    if ( !Layer::init() ) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vector<MenuItem*> MenuItems;
    auto startItem = MenuItemImage::create("buttons/StartNormal.png",
                                           "buttons/StartNormal.png",
                                           CC_CALLBACK_0(HallLayer::menuStartCallback, this));
    auto closeItem = MenuItemImage::create("buttons/CloseNormal.png",
                                           "buttons/CloseSelected.png",
                                           CC_CALLBACK_1(HallLayer::menuCloseCallback, this));

    startItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    MenuItems.pushBack(startItem);
    MenuItems.pushBack(closeItem);

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    auto label = Label::createWithTTF("Game Hall", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    this->addChild(label, 1);

    return true;
}

void HallLayer::menuStartCallback() {
    auto stageFileName = "stage1.plist";

    UserDefault::getInstance()->setStringForKey("nextStageFile", stageFileName);
    Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, GameScene::create()));
}

void HallLayer::menuCloseCallback(Ref* pSender) {
    Director::getInstance()->replaceScene(MenuScene::create());
}