#pragma once
#include "core/entity.h"

#define SPEED_BG 0.5f
#define SPEED_FG 1.0f

void env_handler(entity_t *e)
{
    e->x -= (e->entity_type == ENTITY_FG) ? SPEED_FG : SPEED_BG;
}