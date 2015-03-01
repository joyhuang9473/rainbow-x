#include "StandSituation.h"
#include "../../Role/Role.h"

USING_NS_CC;

void StandSituation::execute(Role* role) {
    role->getSprite()->stopAllActions();
}