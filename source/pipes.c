#include "core/state.h"
#include "core/entity.h"
#include "level.h"
#include "sprites.h"
#include "pipes.h"

#define PIPES_GAP 64
#define PIPE_WIDTH 32.f
#define PIPE_HEIGHT 128.f

#define PIPE_HEIGHT_HALF (PIPE_HEIGHT/2.f)

void pipes_init(entity_t *e)
{
    // TODO : load sprite
    for (size_t i=0; i<PIPES_NO_COLS; i++)
    {
        e[2*i    ].x = PIPE_WIDTH + SCREEN_WIDTH + i*PIPES_OFFSET;
        e[2*i + 1].x = PIPE_WIDTH + SCREEN_WIDTH + i*PIPES_OFFSET;

        // TODO : generate random heights
        e[2*i    ].y = i*10 + PIPE_HEIGHT;
        e[2*i + 1].y = i*10 + PIPE_HEIGHT;
        // TODO : attach sprite
        e[2*i + 1].tx_data.flip_mode = GL_FLIP_H;
    }
    for (size_t j=0; j<PIPES_NO_ENTITIES; j++)
    {
        e[j].active = true;
        e[j].entity_type = ENTITY_PIPE;
        e[j].rx = PIPE_WIDTH/2.f;
        e[j].ry = PIPE_HEIGHT/2.f;
        e[j].vx = LEVEL_SPEED_FG;
        e[j].vy = 0.f;
        
        e[j].tx_data.tx = sprites_load_pipes();
        e[j].tx_data.rotation = TX_ROT_90;
        e[j].tx_data.idx = 1;
    }
}

void pipes_update(entity_t *e)
{
    switch (g_gamestate)
    {
        case IDLE:
            break;
        case PLAY:
            for (size_t j=0; j<PIPES_NO_ENTITIES; j++) {
                e[j].vx = LEVEL_SPEED_FG;
                // update position of pipes column
                e[j].x += e[j].vx;
                // teleport to the back of the stack
                if (e[j].x < -PIPE_WIDTH/2) {
                    e[j].x += PIPES_NO_COLS*PIPES_OFFSET;
                }
            }
            break;
        case HIT:
            break;
        case OVER:
            for (size_t j=0; j<PIPES_NO_ENTITIES; j++) {
                e[j].vx += LEVEL_SPEED_OVER_DECELLERATION;
                // update position of pipes column
                e[j].x += e[j].vx;
            }
            if (e[0].vx >= 0) g_gamestate = MENU;
            break;
        case RESET:
            bool all_off_screen = true;
            for (size_t j=0; j<PIPES_NO_ENTITIES; j++) {
                e[j].vx = 0.f;
                if (j%2) { // bottom row
                    e[j].vy -= LEVEL_SPEED_BG;
                    all_off_screen &= (e[j].y > SCREEN_HEIGHT + PIPE_HEIGHT/2);
                } else { // top row
                    e[j].vy += LEVEL_SPEED_BG;
                    all_off_screen &= (e[j].y < -PIPE_HEIGHT/2);
                }
                e[j].y  += e[j].vy;
            }
            if (all_off_screen) {
                g_gamestate = IDLE;
                for (size_t i=0; i<PIPES_NO_COLS; i++) {
                    e[2*i    ].x = PIPE_WIDTH + SCREEN_WIDTH + i*PIPES_OFFSET;
                    e[2*i + 1].x = PIPE_WIDTH + SCREEN_WIDTH + i*PIPES_OFFSET;

                    // TODO : generate random heights
                    e[2*i    ].y = i*10 - PIPE_HEIGHT_HALF;
                    e[2*i + 1].y = i*10 + PIPES_GAP + PIPE_HEIGHT_HALF;

                    e[2*i    ].vy = 0;
                    e[2*i + 1].vy = 0;
                }
            }
            break;
    }
}

static void pipes_reset(entity_t *e)
{
    for (size_t j=0; j<PIPES_NO_ENTITIES; j++)
    {
        e[j].x += SCREEN_WIDTH + PIPE_WIDTH;
    }
}

void pipes_destroy(entity_t *e)
{
    for (size_t j=0; j<PIPES_NO_ENTITIES; j++)
    {
        if (e[j].tx_data.tx) {
            free(e[j].tx_data.tx);
            e[j].tx_data.tx = NULL;
        }
    }
}