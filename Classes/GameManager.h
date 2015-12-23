#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "GroupEnemy.h"
#include "Entity/Role/Hero.h"

class GameManager {
public:
    GameManager();
    ~GameManager();

    static GameManager* getInstance();

    void readStageInfo(const std::string plistpath);
    void clear();

    CC_SYNTHESIZE(std::string, curMapName, CurMapName);
    CC_SYNTHESIZE(std::string, curStageFile, CurStageFile);
    CC_SYNTHESIZE(std::string, nextStageFile, NextStageFile);
    CC_SYNTHESIZE(std::string, curBgName, CurBgName);

    CC_SYNTHESIZE(int, groupNum, GroupNum);
    CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
    CC_SYNTHESIZE(Hero::HeroType, heroType, HeroType);

    cocos2d::Vector<GroupEnemy*> groupVector;

private:
    static GameManager* instance;

    cocos2d::ValueMap resources;
    cocos2d::ValueMap stageInfo;
};

#endif
