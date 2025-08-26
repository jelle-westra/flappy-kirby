#include "core/state.h"
#include "core/entity.h"
#include "level.h"
#include "pipes.h"

#define PIPES_GAP 128
#define PIPE_WIDTH 32
#define PIPE_HEIGHT 64


void pipes_init(entity_t e[])
{
    // TODO : load sprite
    for (size_t i=0; i<PIPES_NO_COLS; i++)
    {
        e[2*i    ].x = SCREEN_WIDTH + i*PIPES_OFFSET;
        e[2*i + 1].x = SCREEN_WIDTH + i*PIPES_OFFSET;

        // TODO : generate random heights
        e[2*i    ].y = i*10;
        e[2*i + 1].y = i*10 + PIPES_GAP;
        // TODO : attach sprite
    }
    for (size_t j=0; j<PIPES_NO_ENTITIES; j++)
    {
        e[j].active = true;
        e[j].entity_type = ENTITY_PIPE;
        e[j].rx = PIPE_WIDTH/2;
        e[j].ry = PIPE_HEIGHT/2;
        e[j].vx = LEVEL_SPEED_FG;
        e[j].vy = 0.f;
    }
}

void pipes_update(entity_t e[])
{
    for (size_t j=0; j<PIPES_NO_ENTITIES; j++) e[j].x += e[j].vx;

    switch (g_gamestate)
    {
    case IDLE:
        /* code */
        for (size_t j=0; j<PIPES_NO_ENTITIES; j++) e[j].vx = LEVEL_SPEED_FG;
        break;
    case PLAY:
        for (size_t j=0; j<PIPES_NO_ENTITIES; j++) e[j].vx = LEVEL_SPEED_FG;
        break;
    case OVER:
        for (size_t j=0; j<PIPES_NO_ENTITIES; j++) 
        {
            e[j].vx += LEVEL_SPEED_OVER_DECELLERATION;
        }
        if (e[0].vx >= 0) g_gamestate = MENU;
        break;
    default:
        break;
    }
}
void pipes_destroy(entity_t e[]);