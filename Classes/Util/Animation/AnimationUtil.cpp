#include "AnimationUtil.h"

USING_NS_CC;

static Animation* createAnimWithFrameName(const char* name) {
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame *> frameArray;
    SpriteFrame* frame = NULL;
    int index = 1;
    
    do {
        frame = frameCache->getSpriteFrameByName(String::createWithFormat("%s%d.png", name, index++)->getCString());
        
        if (frame == NULL) {
            break;
        }
        
        frameArray.pushBack(frame);
    } while(true);
    
    Animation* animation = Animation::createWithSpriteFrames(frameArray);
    
    return animation;
}