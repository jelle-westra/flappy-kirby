#pragma once
#include "core/entity.h"

#define KIRBY_KEY_JUMP (KEY_A|KEY_B)

#define KIRBY_SPRITE_WIDTH 32
#define KIRBY_X SCREEN_WIDTH/3 
#define KIRBY_Y SCREEN_HEIGHT/2

#define KIRBY_COLLIDER_MARGIN_FACTOR 0.95f
#define KIRBY_COLLIDER_RADIUS (KIRBY_COLLIDER_MARGIN_FACTOR*KIRBY_SPRITE_WIDTH/2)


void kirby_init(entity_t *e);
void kirby_update(entity_t *e);
void kirby_destroy(entity_t *e);