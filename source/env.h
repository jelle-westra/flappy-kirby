#pragma once
#include "core/entity.h"
#include "level.h"

#define ENV_NO_ENTITIES 0

void env_handler(entity_t *e);
// {
//     e->x -= (e->entity_type == ENTITY_FG) ? LEVEL_SPEED_FG : LEVEL_SPEED_BG;
// }