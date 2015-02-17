#include "StandState.h"
#include "Role.h"

void StandState::execute(Role* role) {
    role->stand();
}