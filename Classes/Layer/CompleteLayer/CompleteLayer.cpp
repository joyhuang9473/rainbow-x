#include "CompleteLayer.h"

bool CompleteLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}
