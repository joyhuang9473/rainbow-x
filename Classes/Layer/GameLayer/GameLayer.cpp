#include "GameLayer.h"
#include "VisibleRect.h"
#include "../../Controller/OperateController.h"
#include "../../Controller/AIController.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

#define FRAMECACHE SpriteFrameCache::getInstance()
#define PTM_RATIO 32

bool GameLayer::init() {
    if( ! Layer::init() ) {
        return false;
    }

    this->initPhysics();

    // Map
    auto map = TMXTiledMap::create("maps/floor.tmx");

    // Hero
    auto player = Hero::createWithHeroType(Hero::HeroType::KISI);
    player->getFSM()->doEvent("stand");
    player->setTag(SpriteTag::SPRITE_HERO);
    this->setPlayer(map, player);
    this->addBoxBodyForRole(player);
    this->m_player = player;

    // Enemy
    auto enemy = Enemy::createWithEnemyType(Enemy::EnemyType::GNU);
    enemy->getFSM()->doEvent("stand");
    enemy->setTag(SpriteTag::SPRITE_ENEMY);
    this->setEnemy(map, enemy, player);
    this->addBoxBodyForRole(enemy);
    
    this->addChild(map, -1);
    this->addChild(player);
    this->addChild(enemy);

    this->schedule(schedule_selector(GameLayer::updateBoxBody));
    this->scheduleUpdate();
    return true;
}

void GameLayer::setPlayer(TMXTiledMap* map, Hero* hero) {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    hero->setTiledMap(map);
    hero->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    OperateController* operateController = OperateController::create();
    operateController->registerWithKeyboardDispatcher();
    operateController->setRole(hero);

    hero->setController(operateController);
    hero->addChild(operateController);
}

void GameLayer::setEnemy(TMXTiledMap* map, Enemy* enemy, Hero* target) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    enemy->setTiledMap(map);
    enemy->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
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

void GameLayer::update(float delta) {}

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

void GameLayer::addBoxBodyForRole(Role* role) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(role->getPositionX() / PTM_RATIO, role->getPositionY() / PTM_RATIO);
    bodyDef.userData = role;

    b2Body* body = this->m_world->CreateBody(&bodyDef);

    int num = 5;
    b2Vec2 verts[] = {
        b2Vec2(-26.0f / PTM_RATIO, 39.1f / PTM_RATIO),
        b2Vec2(26.1f / PTM_RATIO, 38.1f / PTM_RATIO),
        b2Vec2(27.1f / PTM_RATIO, -38.0f / PTM_RATIO),
        b2Vec2(-25.9f / PTM_RATIO, -38.0f / PTM_RATIO),
        b2Vec2(-25.9f / PTM_RATIO, 39.0f / PTM_RATIO),
    };

    b2FixtureDef fixtureDef;
    b2PolygonShape spriteShape;
    spriteShape.Set(verts, num);
    fixtureDef.shape = &spriteShape;
    fixtureDef.density = 10.0f;
    fixtureDef.isSensor = true;

    body->CreateFixture(&fixtureDef);
}

void GameLayer::updateBoxBody(float dt) {
    this->m_world->Step(dt, 10, 10);

    std::vector<b2Body*> toDestroy;

    // check all body in physics world
    for (b2Body* body = this->m_world->GetBodyList() ; body ; body = body->GetNext()) {
        if (body->GetUserData() != NULL) {
            Role* role = (Role*)body->GetUserData();
            if (role->getHealth() <= 0) {
                role->getFSM()->doEvent("die");
                role->removeChild(role->getController());
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
        }
        this->m_world->DestroyBody(body);
    }
}
