#include "InjuredState.h"
#include "Role.h"

void InjuredState::execute(Role* role) {
    role->injured();
}