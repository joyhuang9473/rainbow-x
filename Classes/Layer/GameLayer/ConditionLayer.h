#ifndef __CONDITION_LAYER_H__
#define __CONDITION_LAYER_H__

#include "cocos2d.h"

class ConditionLayer : public cocos2d::Layer {
public:
    virtual bool init();

    CREATE_FUNC(ConditionLayer);

    void menuOptionCallback();

    void menuCloseCallback(cocos2d::Ref* pSender);

};

#endif