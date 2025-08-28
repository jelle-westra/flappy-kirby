#pragma once
#include "core/entity.h"

#define SCOREBOARD_NO_ENTITIES 6

void scoreboard_init(entity_t *e);
void scoreboard_update(entity_t *e);
void scoreboard_reset(entity_t *e);