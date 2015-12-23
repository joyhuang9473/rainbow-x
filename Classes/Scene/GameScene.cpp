#include "GameScene.h"
#include "../Layer/GameLayer/GameLayer.h"
#include "HallScene.h"
#include "../Layer/GameLayer/ConditionLayer.h"

USING_NS_CC;

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    Director::getInstance()->getEventDispatcher()->addCustomEventListener("missionComplete", CC_CALLBACK_0(GameScene::createCompleteDialog, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("missionFailed", CC_CALLBACK_0(GameScene::createFailedDialog, this));

    this->addChild(GameLayer::create());
    this->addChild(ConditionLayer::create());
    return true;
}

void GameScene::createCompleteDialog() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto label = Label::createWithTTF("Mission Complete", "Marker Felt.ttf", 72);

    label->setPosition(Vec2(visibleSize.width/2, 2*visibleSize.height/3));
    this->addChild(label);

    auto menuItem = MenuItemImage::create("signHangingOption.png",
                                          "signHangingOption.png",
                                          CC_CALLBACK_0(GameScene::menuCallback, this));
    auto menu = Menu::create(menuItem, NULL);
    this->addChild(menu);
}

void GameScene::createFailedDialog() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto label = Label::createWithTTF("Mission Failed", "Marker Felt.ttf", 72);

    label->setPosition(Vec2(visibleSize.width/2, 2*visibleSize.height/3));
    this->addChild(label);

    auto menuItem = MenuItemImage::create("signHangingOption.png",
                                          "signHangingOption.png",
                                          CC_CALLBACK_0(GameScene::menuCallback, this));
    auto menu = Menu::create(menuItem, NULL);
    this->addChild(menu);
}

void GameScene::menuCallback() {
    Director::getInstance()->replaceScene(HallScene::create());
}
