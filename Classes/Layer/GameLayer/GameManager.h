#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "../../Entity/Role/Role.h"
#include "../HallLayer/GroupEnemy.h"

class GameManager {
public:
    cocos2d::Vector<GroupEnemy*> groupVector;

    static GameManager* getInstance();
    void clear();

    CC_SYNTHESIZE(int, groupNum, GroupNum);
    CC_SYNTHESIZE(std::string, curMapName, CurMapName);
    CC_SYNTHESIZE(std::string, currStageFile, CurrStageFile);
    CC_SYNTHESIZE(std::string, nextStageFile, NextStageFile);
    CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
    CC_SYNTHESIZE(std::string, curBgName, CurBgName);

private:
    static GameManager* instance;
};

#endif
