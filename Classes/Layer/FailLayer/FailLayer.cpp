#include "FailLayer.h"

bool FailLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}
