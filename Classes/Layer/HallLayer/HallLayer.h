#ifndef __HALL_LAYER_H__
#define __HALL_LAYER_H__

#include "cocos2d.h"

class HallLayer : public cocos2d::Layer {
public:
    virtual bool init();
    
    CREATE_FUNC(HallLayer);

    void menuStartCallback();

    void menuCloseCallback(Ref* pSender);

};

#endif
