#include "GameLayer.h"
#include "VisibleRect.h"
#include "Box2D/Box2D.h"
#include "GameManager.h"
#include "../../Controller/OperateController.h"
#include "../../Controller/AIController.h"
#include "../../Scene/CompleteScene.h"
#include "../../Scene/FailScene.h"
#include "../../Scene/GameScene.h"

USING_NS_CC;

#define PTM_RATIO 32
#define GAMEMANAGER GameManager::getInstance()

bool GameLayer::init() {
    if( ! Layer::init() ) {
        return false;
    }

    this->initPhysics();

    // Stage
    auto stageFile = GAMEMANAGER->getCurStageFile();
    if (stageFile == "") {
        stageFile = "country_road.plist";
    }

    GAMEMANAGER->readStageInfo(stageFile);
    this->isSuccessful = false;

    // Map
    std::vector<std::string> searchPaths;
    searchPaths.push_back("Map");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    this->m_map = TMXTiledMap::create(GAMEMANAGER->getCurMapName());

    // Player
    auto heroType = GAMEMANAGER->getHeroType();
    if (!heroType) {
        heroType = Hero::HeroType::KISI;
    }

    auto player = Hero::createWithHeroType(heroType);
    player->getFSM()->doEvent("stand");
    player->setTag(SpriteTag::SPRITE_HERO);
    this->setPlayer(this->m_map, player);
    this->addBoxBodyForRole(player);
    this->m_player = player;

    // Goup Enemy
    this->numsOfEnemy = 0;
    this->enemyGroupCounter = 0;

    this->addChild(this->m_map, -1);
    this->addChild(this->m_player);

    this->schedule(schedule_selector(GameLayer::logic));
    this->schedule(schedule_selector(GameLayer::updateActionScope));
    this->schedule(schedule_selector(GameLayer::updateBoxBody));
    return true;
}

void GameLayer::initPhysics() {
    b2Vec2 gravity;
    gravity.Set(0.0f, 0.0f);
    
    this->m_world = new b2World(gravity);
    this->m_world->SetAllowSleeping(false);
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    
    b2Body* groundBody = this->m_world->CreateBody(&groundBodyDef);
    b2EdgeShape groundBox;
    
    // bottom
    groundBox.Set(b2Vec2(VisibleRect::leftBottom().x / PTM_RATIO, VisibleRect::leftBottom().y / PTM_RATIO),
                  b2Vec2(VisibleRect::rightBottom().x / PTM_RATIO, VisibleRect::rightBottom().y / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
    
    // right
    groundBox.Set(b2Vec2(VisibleRect::rightBottom().x / PTM_RATIO, VisibleRect::rightBottom().y / PTM_RATIO),
                  b2Vec2(VisibleRect::rightTop().x / PTM_RATIO, VisibleRect::rightTop().y / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
    
    // top
    groundBox.Set(b2Vec2(VisibleRect::leftTop().x / PTM_RATIO, VisibleRect::leftTop().y / PTM_RATIO),
                  b2Vec2(VisibleRect::rightTop().x / PTM_RATIO, VisibleRect::rightTop().y / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
    
    // left
    groundBox.Set(b2Vec2(VisibleRect::leftBottom().x / PTM_RATIO, VisibleRect::leftBottom().y / PTM_RATIO),
                  b2Vec2(VisibleRect::leftTop().x / PTM_RATIO, VisibleRect::leftTop().y / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
    
    this->m_contactListener = new ContactListener();
    this->m_world->SetContactListener(this->m_contactListener);
}

void GameLayer::setPlayer(TMXTiledMap* map, Hero* hero) {
    TMXObjectGroup* playerObject = map->getObjectGroup("player");
    ValueMap startPoint = playerObject->getObject("start_point");

    hero->setTiledMap(map);
    hero->setPosition(Vec2(startPoint["x"].asFloat(), startPoint["y"].asFloat()));

    OperateController* operateController = OperateController::create();
    operateController->registerWithKeyboardDispatcher();
    operateController->setRole(hero);

    hero->setController(operateController);
    hero->addChild(operateController);
}

void GameLayer::setEnemy(TMXTiledMap* map, Hero* enemy, Hero* target) {
    TMXObjectGroup* enemyGroupObject = map->getObjectGroup(StringUtils::format("enemy_group%d", this->enemyGroupCounter));
    ValueMap startPoint = enemyGroupObject->getObject(StringUtils::format("start_point%d", this->numsOfEnemy));

    enemy->setTiledMap(map);
    enemy->setPosition(Vec2(startPoint["x"].asFloat(), startPoint["y"].asFloat()));

    AIController* aiController = AIController::create();
    aiController->setRole(enemy);
    aiController->setTarget(target);

    enemy->setController(aiController);
    enemy->addChild(aiController);
}

bool GameLayer::collisionDetection(const BoundingBox &hitBox, const BoundingBox &bodyBox) {
    Rect hitRect = hitBox.actual;
    Rect bodyRect = bodyBox.actual;

    if (hitRect.intersectsRect(bodyRect)) {
        return true;
    }
    return false;
}

void GameLayer::addBoxBodyForRole(Role* role) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(role->getPositionX() / PTM_RATIO, role->getPositionY() / PTM_RATIO);
    bodyDef.userData = role;

    b2Body* body = this->m_world->CreateBody(&bodyDef);
    int num = 5;
    b2Vec2 verts[] = {
        b2Vec2(-39.0f / PTM_RATIO, 39.0f / PTM_RATIO),
        b2Vec2(39.0f / PTM_RATIO, 39.0f / PTM_RATIO),
        b2Vec2(39.0f / PTM_RATIO, -39.0f / PTM_RATIO),
        b2Vec2(-39.0f / PTM_RATIO, -39.0f / PTM_RATIO),
        b2Vec2(-39.0f / PTM_RATIO, 39.0f / PTM_RATIO),
    };

    b2FixtureDef fixtureDef;
    b2PolygonShape spriteShape;
    spriteShape.Set(verts, num);
    fixtureDef.shape = &spriteShape;
    fixtureDef.density = 10.0f;
    fixtureDef.isSensor = true;

    body->CreateFixture(&fixtureDef);
}

GroupEnemy* GameLayer::currentGroup() {
    GroupEnemy* groupEnemy;

    if (!GAMEMANAGER->groupVector.empty()) {
        groupEnemy = (GroupEnemy*)GAMEMANAGER->groupVector.at(this->enemyGroupCounter);
    } else {
        groupEnemy = nullptr;
    }

    return groupEnemy;
}

void GameLayer::nextGroup() {
    if (this->enemyGroupCounter < GAMEMANAGER->getGroupNum()-1) {
        ++this->enemyGroupCounter;
    } else {
        this->isSuccessful = true;
    }
}

void GameLayer::addEnemy() {
    GroupEnemy* groupEnemy = this->currentGroup();

    if (groupEnemy == nullptr) {
        return;
    }
    if (groupEnemy->getIsFinishedAddGroup()) {
        return;
    }
    if (groupEnemy->getEnemyTotal() <= 0) {
        groupEnemy->setIsFinishedAddGroup(true);
        return;
    }

    Hero* enemy = nullptr;

    if (groupEnemy->getType1Total() > 0) {
        enemy = Hero::createWithHeroType(Hero::HeroType::GNU);
        groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
    } else if (groupEnemy->getType2Total() > 0) {
        enemy = Hero::createWithHeroType(Hero::HeroType::KISI);
        groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
    }

    enemy->getFSM()->doEvent("stand");
    enemy->setTag(SpriteTag::SPRITE_ENEMY);
    this->setEnemy(this->m_map, enemy, this->m_player);
    this->addBoxBodyForRole(enemy);
    this->addChild(enemy);

    this->numsOfEnemy += 1;
    groupEnemy->setEnemyTotal(groupEnemy->getType1Total() + groupEnemy->getType2Total());
}

void GameLayer::logic(float dt) {
    if (this->isSuccessful) {
        TMXObjectGroup* playerObject = this->m_map->getObjectGroup("player");
        ValueMap accessPoint = playerObject->getObject("access_point");

        if (this->m_player->getTagPosition().x < accessPoint["x"].asFloat()) {
            return;
        }

        auto nextStageFile = GAMEMANAGER->getNextStageFile();

        if (nextStageFile != "") {
            GAMEMANAGER->setCurStageFile(nextStageFile);
            Director::getInstance()->replaceScene(GameScene::create());
        } else {
            Director::getInstance()->replaceScene(CompleteScene::create());
        }
        return;
    }

    GroupEnemy* groupEnemy = this->currentGroup();

    if (groupEnemy == nullptr) {
        return;
    }
    if (groupEnemy->getIsFinishedAddGroup() && this->numsOfEnemy == 0) {
        this->nextGroup();
    }

    this->addEnemy();
}

void GameLayer::updateActionScope(float dt) {
    auto visibleSize = Size(this->m_map->getMapSize().width * this->m_map->getTileSize().width,
                            this->m_map->getMapSize().height * this->m_map->getTileSize().height);

    for (b2Body* body = this->m_world->GetBodyList() ; body ; body = body->GetNext()) {
        if (body->GetUserData() != NULL) {
            Role* role = (Role*)body->GetUserData();
            Size spriteSize = role->getSprite()->getDisplayFrame()->getRect().size;
            Point pos = role->getTagPosition();

            pos.x = (pos.x < visibleSize.width - spriteSize.width) ? pos.x : visibleSize.width - spriteSize.width;
            pos.x = (pos.x > spriteSize.width) ? pos.x : spriteSize.width;
            pos.y = (pos.y < visibleSize.height - spriteSize.height) ? pos.y : visibleSize.height - spriteSize.height;
            pos.y = (pos.y > spriteSize.height) ? pos.y : spriteSize.height;

            role->setTagPosition(pos.x, pos.y);
        }
    }
}

void GameLayer::updateBoxBody(float dt) {
    this->m_world->Step(dt, 10, 10);

    std::vector<b2Body*> toDestroy;

    // check all body in physics world
    for (b2Body* body = this->m_world->GetBodyList() ; body ; body = body->GetNext()) {
        if (body->GetUserData() != NULL) {
            Role* role = (Role*)body->GetUserData();

            // update boxbody
            body->SetTransform(b2Vec2(role->getTagPosition().x / PTM_RATIO, role->getTagPosition().y / PTM_RATIO), 0);

            if (role->getFSM()->getCurrState() == "dead") {
                role->removeChild(role->getController());

                if (role->getTag() == SpriteTag::SPRITE_ENEMY) {
                    toDestroy.push_back(body);
                }
            }
        }
    }

    std::vector<Contact>::iterator iter;
    for (iter = this->m_contactListener->m_contacts.begin() ; iter != this->m_contactListener->m_contacts.end() ; ++iter) {
        Contact contact = *(iter);
        b2Body* bodyA = contact.fixtureA->GetBody();
        b2Body* bodyB = contact.fixtureB->GetBody();
        
        if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
            Role* roleA = (Role*)bodyA->GetUserData();
            Role* roleB = (Role*)bodyB->GetUserData();

            if (roleA->getTag() == roleB->getTag()) {
                continue;
            }

            if (
                roleA->getFSM()->getCurrState() == "attacking"
             || roleA->getFSM()->getCurrState() == "skilling"
            ) {
                if (this->collisionDetection(roleA->getHitBox(), roleB->getBodyBox())) {
                    roleB->beHit(roleA->getAttack());
                }
            } else if (
                roleB->getFSM()->getCurrState() == "attacking"
             || roleB->getFSM()->getCurrState() == "skilling"
            ) {
                if (this->collisionDetection(roleB->getHitBox(), roleA->getBodyBox())) {
                    roleA->beHit(roleB->getAttack());
                }
            }
        }
    }

    // remove dead role
    std::vector<b2Body*>::iterator iter2;
    for (iter2 = toDestroy.begin() ; iter2 != toDestroy.end() ; ++iter2) {
        b2Body* body = *(iter2);

        if (body->GetUserData() != NULL) {
            Role* role = (Role*)body->GetUserData();
            this->removeChild(role);
            --this->numsOfEnemy;
        }
        this->m_world->DestroyBody(body);
    }
}
