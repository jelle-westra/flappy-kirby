#include "state.h"
#include "nds.h"

gamestate_t g_gamestate;
uint32_t g_frame;
uint32_t g_input;
uint32_t g_score;

void state_init()
{
    g_frame = 0;
    state_reset();
}

void state_update()
{
    scanKeys();
    g_frame++;
    g_input = keysDown();
}

void state_reset()
{
    g_gamestate = RESET;
    g_input = 0;
}