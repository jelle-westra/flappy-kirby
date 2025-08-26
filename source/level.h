#pragma once
#include "pipes.h"
#include "env.h"

#define LEVEL_SPEED_FG -1.0f
#define LEVEL_SPEED_BG -0.5f
#define LEVEL_SPEED_OVER_DECELLERATION 0.005f

#define LEVEL_NO_ENITITES 1+PIPES_NO_ENTITIES+ENV_NO_ENTITIES

void collision_init();
void collision_update(entity_t *kirby, entity_t pipes[]);