#pragma once
#include "core/entity.h"

#define KIRBY_KEY_JUMP (KEY_A|KEY_B)

void kirby_init(entity_t *e);
void kirby_update(entity_t *e);
void kirby_destroy(entity_t *e);