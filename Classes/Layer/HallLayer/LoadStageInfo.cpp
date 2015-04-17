#include "LoadStageInfo.h"
#include "../GameLayer/GameManager.h"

USING_NS_CC;

#define GAMEMANAGER GameManager::getInstance()

LoadStageInfo::LoadStageInfo() {}

LoadStageInfo::~LoadStageInfo() {
    this->clearAll();
}

bool LoadStageInfo::init() {
    std::vector<std::string> searchPaths;
    searchPaths.push_back("Settings");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    return true;
}

bool LoadStageInfo::initWithPlist(const std::string plistpath) {
    bool bRet = false;

    do {
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(plistpath.c_str());
        this->resources = dict["resources"].asValueMap();
        this->stageInfo = dict["stageInfo"].asValueMap();
        bRet = true;
    } while (0);

    return bRet;
}

void LoadStageInfo::clearAll() {
    this->resources.clear();
    this->stageInfo.clear();
}

void LoadStageInfo::readStageInfo() {
    auto currStage = this->stageInfo["currStage"].asString();
    auto nextStage = this->stageInfo["nextStage"].asString();
    ValueMap& groupDict = this->stageInfo["group"].asValueMap();
    auto groupTotal = groupDict.size();
    auto curMapName = this->resources["map"].asString();
    auto curBgName = this->resources["image"].asString();

    GAMEMANAGER->setCurrStageFile(currStage);
    GAMEMANAGER->setNextStageFile(nextStage);
    GAMEMANAGER->setGroupNum(groupTotal);
    GAMEMANAGER->setCurMapName(curMapName);
    GAMEMANAGER->setCurBgName(curBgName);

    for (auto iter = groupDict.begin() ; iter != groupDict.end() ; ++iter) {
        ValueMap& group = iter->second.asValueMap();
        auto type1Num = group["type1Num"].asInt();
        auto type2Num = group["type2Num"].asInt();
        auto type1Hp = group["type1Hp"].asInt();
        auto type2Hp = group["type2Hp"].asInt();

        GroupEnemy* groupEnemy = GroupEnemy::create()->initGroupEnemy(type1Num, type1Hp, type2Num, type2Hp);
        GAMEMANAGER->groupVector.pushBack(groupEnemy);
    }
}
