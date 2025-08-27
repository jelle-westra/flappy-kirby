#pragma once
#include "core/entity.h"


#define PIPES_OFFSET 128

#define PIPES_NO_COLS ((int)SCREEN_WIDTH/PIPES_OFFSET + 1)
#define PIPES_NO_ENTITIES 2*PIPES_NO_COLS

void pipes_init(entity_t *e);
void pipes_update(entity_t *e);
void pipes_destroy(entity_t *e);