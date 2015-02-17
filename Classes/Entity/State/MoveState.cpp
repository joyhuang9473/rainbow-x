#include "MoveState.h"
#include "Role.h"

void MoveState::execute(Role* role) {
    role->move();
}