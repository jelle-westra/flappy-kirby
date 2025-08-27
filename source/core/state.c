#include "state.h"

gamestate_t g_gamestate;
uint32_t g_frame;
uint32_t g_input;
uint32_t g_score;

void state_init()
{
    g_frame = 0;
    state_reset();
}

void state_reset()
{
    g_gamestate = RESET;
    g_input = 0;
}