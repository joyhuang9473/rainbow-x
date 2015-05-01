#include "GameManager.h"

USING_NS_CC;

GameManager* GameManager::instance;

GameManager::GameManager() {
    std::vector<std::string> searchPaths;
    searchPaths.push_back("Settings");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
}

GameManager::~GameManager() {}

GameManager* GameManager::getInstance() {
    if (instance == nullptr) {
        instance = new GameManager();
    }
    return instance;
}

void GameManager::readStageInfo(const std::string plistpath) {
    this->clear();

    do {
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(plistpath.c_str());
        this->resources = dict["resources"].asValueMap();
        this->stageInfo = dict["stageInfo"].asValueMap();
    } while (0);

    ValueMap& groupDict = this->stageInfo["group"].asValueMap();

    this->setCurStageFile(this->stageInfo["curStage"].asString());
    this->setNextStageFile(this->stageInfo["nextStage"].asString());
    this->setGroupNum(groupDict.size());
    this->setCurMapName(this->resources["map"].asString());
    this->setCurBgName(this->resources["image"].asString());

    for (auto iter = groupDict.begin() ; iter != groupDict.end() ; ++iter) {
        ValueMap& group = iter->second.asValueMap();
        auto type1Num = group["type1Num"].asInt();
        auto type2Num = group["type2Num"].asInt();
        auto type1Hp = group["type1Hp"].asInt();
        auto type2Hp = group["type2Hp"].asInt();

        GroupEnemy* groupEnemy = GroupEnemy::create()->initGroupEnemy(type1Num, type1Hp, type2Num, type2Hp);
        this->groupVector.pushBack(groupEnemy);
    }
}

void GameManager::clear() {
    this->groupVector.clear();
    this->resources.clear();
    this->stageInfo.clear();
}
