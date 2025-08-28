#pragma once
#include "pipes.h"
#include "env.h"

#define LEVEL_SPEED_FG -1.0f
#define LEVEL_SPEED_BG -0.5f
#define LEVEL_SPEED_OVER_DECELLERATION 0.005f

#define LEVEL_NO_ENITITES 1+PIPES_NO_ENTITIES+ENV_NO_ENTITIES+SCOREBOARD_NO_ENTITIES

extern int hit_timeout;

void level_init();
void level_reset();
void level_update(entity_t *kirby, entity_t *pipes, entity_t *scoreboard);