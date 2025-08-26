#pragma once
#include <stdint.h>

typedef enum { IDLE, PLAY, OVER, MENU } gamestate_t;

extern gamestate_t g_gamestate;
extern uint32_t g_frame;
extern uint32_t g_input;