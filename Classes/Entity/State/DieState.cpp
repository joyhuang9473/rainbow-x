#include "DieState.h"
#include "Role.h"

void DieState::execute(Role* role) {
    role->die();
}