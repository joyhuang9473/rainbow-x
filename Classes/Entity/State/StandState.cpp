#include "StandState.h"
#include "Role.h"
#include "MoveState.h"

void StandState::execute(Role* role) {
    role->runMoveAction();
    role->getFSM()->changeState(new MoveState());
}