#pragma once
#include "core/entity.h"

#define ENV_NO_ENTITIES 2

void env_init(entity_t *e);
void env_update(entity_t *e);
void env_destroy(entity_t *e);