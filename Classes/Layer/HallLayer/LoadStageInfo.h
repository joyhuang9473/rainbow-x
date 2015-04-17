#ifndef __LOADSTAGE_INFO_H__
#define __LOADSTAGE_INFO_H__

#include "cocos2d.h"

class LoadStageInfo : public cocos2d::Node {
public:
    LoadStageInfo();
    ~LoadStageInfo();

    virtual bool init();
    CREATE_FUNC(LoadStageInfo);

    bool initWithPlist(const std::string plistpath);
    void readStageInfo();
    void clearAll();

private:
    cocos2d::ValueMap resources;
    cocos2d::ValueMap stageInfo;
};

#endif
