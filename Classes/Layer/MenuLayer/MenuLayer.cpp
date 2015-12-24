#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "../../Scene/HallScene.h"
#include "../../Entity/Role/Hero.h"
#include "../../Controller/RobotController.h"

USING_NS_CC;
using namespace CocosDenshion;

#define VISIBLESIZE Director::getInstance()->getVisibleSize()

bool MenuLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // Audio
    SimpleAudioEngine::getInstance()->playBackgroundMusic("magic_town.mp3", true);

    // Background
    this->m_map = TMXTiledMap::create("menu.tmx");
    this->addChild(this->m_map);
    Size size = this->m_map->getLayer("background")->getContentSize();
    this->m_map->getLayer("background")->setPositionX(size.width);

    this->setBackground();

    // Menu
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vector<MenuItem*> MenuItems;

    auto aboutItem = MenuItemImage::create("signAbout.png",
                                           "signAboutEnable.png",
                                           CC_CALLBACK_0(MenuLayer::menuAboutCallback, this));

    auto startItem = MenuItemImage::create("signStart.png",
                                           "signStartEnable.png",
                                           CC_CALLBACK_0(MenuLayer::menuStartCallback, this));

    auto closeItem = MenuItemImage::create("signExit.png",
                                           "signExitEnable.png",
                                           CC_CALLBACK_1(MenuLayer::menuCloseCallback, this));

    aboutItem->setPosition(Vec2(origin.x + VISIBLESIZE.width/2 - aboutItem->getContentSize().width*2, origin.y + VISIBLESIZE.height/3));
    startItem->setPosition(Vec2(origin.x + VISIBLESIZE.width/2, origin.y + VISIBLESIZE.height/3));
    closeItem->setPosition(Vec2(origin.x + VISIBLESIZE.width/2 + closeItem->getContentSize().width*2, origin.y + VISIBLESIZE.height/3));

    MenuItems.pushBack(aboutItem);
    MenuItems.pushBack(startItem);
    MenuItems.pushBack(closeItem);

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Rainbow-x", "Marker Felt.ttf", 72);
    label->setColor(Color3B(30, 139, 195));
    label->setPosition(Vec2(origin.x + VISIBLESIZE.width/2,
                            origin.y + VISIBLESIZE.height - 2*label->getContentSize().height));
    this->addChild(label, 1);

    this->scheduleUpdate();
    return true;
}

void MenuLayer::menuAboutCallback() {
    // TODO
    log("About!");
}

void MenuLayer::menuStartCallback() {
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(HallScene::create());
}

void MenuLayer::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MenuLayer::setBackground() {
    // Conductor
    this->m_conductor = new Role();
    this->m_conductor->setPosition(Vec2(20, VISIBLESIZE.height/5));
    this->addChild(this->m_conductor);

    // Role
    auto role = Hero::createWithHeroType(Hero::HeroType::KISI);
    role->setTiledMap(this->m_map);
    role->getFSM()->doEvent("stand");
    role->setPosition(Vec2(VISIBLESIZE.width - 100, VISIBLESIZE.height/4));
    role->hideHealthProgress();

    RobotController* robotController = RobotController::create();
    robotController->setRole(role);
    robotController->setTarget(this->m_conductor);

    role->setController(robotController);
    role->addChild(robotController);
    this->addChild(role);
}

void MenuLayer::update(float dt) {
    int posBgLayer = this->m_map->getLayer("background")->getPositionX();
    int posRepeatBgLayer = this->m_map->getLayer("background_repetition")->getPositionX();
    int speed = 1;

    posBgLayer -= speed;
    posRepeatBgLayer -= speed;

    Size size = this->m_map->getLayer("background")->getContentSize();

    if (posBgLayer <= -size.width) {
        posBgLayer = size.width;
    }
    if (posRepeatBgLayer <= -size.width) {
        posRepeatBgLayer = size.width;
    }

    this->m_map->getLayer("background")->setPositionX(posBgLayer);
    this->m_map->getLayer("background_repetition")->setPositionX(posRepeatBgLayer);

    // Conductor
    Point pos = this->m_conductor->getPosition();

    if (pos.x > VISIBLESIZE.width) {
        pos.x = 0;
    } else {
        pos.x += 10;
    }

    this->m_conductor->setPosition(pos);
}
