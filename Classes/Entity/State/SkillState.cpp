#include "SkillState.h"
#include "Role.h"

void SkillState::execute(Role* role) {
    role->skill();
}