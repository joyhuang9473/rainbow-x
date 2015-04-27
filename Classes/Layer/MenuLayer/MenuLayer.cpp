#include "MenuLayer.h"
#include "../../Scene/HallScene.h"
#include "../../Entity/Role/Hero.h"
#include "../../Controller/AIController.h"

USING_NS_CC;

bool MenuLayer::init() {
    if ( !Layer::init() ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
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

    aboutItem->setPosition(Vec2(origin.x + visibleSize.width/2 - aboutItem->getContentSize().width*2, origin.y + visibleSize.height/3));
    startItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/3));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width/2 + closeItem->getContentSize().width*2, origin.y + visibleSize.height/3));

    MenuItems.pushBack(aboutItem);
    MenuItems.pushBack(startItem);
    MenuItems.pushBack(closeItem);

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Aslan-Rainbow-x", "fonts/Marker Felt.ttf", 72);

    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - 2*label->getContentSize().height));

    this->addChild(label, 1);

    this->setBackground();

    this->scheduleUpdate();
    return true;
}

void MenuLayer::menuAboutCallback() {
    // TODO
    CCLOG("About!");
}

void MenuLayer::menuStartCallback() {
    CCLOG("START!");

    Director::getInstance()->replaceScene(HallScene::create());
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

void MenuLayer::setBackground() {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // Map
    std::vector<std::string> searchPaths;
    searchPaths.push_back("Map");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    this->m_map = TMXTiledMap::create("menu.tmx");
    this->addChild(this->m_map);

    Size size = this->m_map->getLayer("background")->getContentSize();
    this->m_map->getLayer("background")->setPositionX(size.width);

    // Conductor
    this->m_conductor = new Role();
    this->m_conductor->setPosition(Vec2(20, visibleSize.height/5));
    this->addChild(this->m_conductor);

    // Role
    auto role = Hero::createWithHeroType(Hero::HeroType::KISI);
    role->getFSM()->doEvent("stand");
    role->setTiledMap(this->m_map);
    role->setPosition(Vec2(visibleSize.width - 100, visibleSize.height/4));
    
    AIController* aiController = AIController::create();
    aiController->setRole(role);
    aiController->setTarget(this->m_conductor);
    role->setController(aiController);
    role->addChild(aiController);
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
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point pos = this->m_conductor->getPosition();

    if (pos.x > visibleSize.width) {
        pos.x = 0;
    } else {
        pos.x += 10;
    }

    this->m_conductor->setPosition(pos);
}
