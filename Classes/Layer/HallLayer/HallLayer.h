#ifndef __HALL_LAYER_H__
#define __HALL_LAYER_H__

#include "cocos2d.h"
#include "LoadStageInfo.h"

class HallLayer : public cocos2d::Layer {
public:
    virtual bool init();
    
    CREATE_FUNC(HallLayer);

    void menuStartCallback();

    void menuCloseCallback(Ref* pSender);

private:
    LoadStageInfo* m_info;
};

#endif
