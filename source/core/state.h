#pragma once
#include <stdint.h>

typedef enum { IDLE, PLAY, HIT, OVER, MENU, RESET } gamestate_t;

extern gamestate_t g_gamestate;
extern uint32_t g_frame;
extern uint32_t g_input;

void state_init();
void state_update();
void state_reset();