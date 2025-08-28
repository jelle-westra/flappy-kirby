#include "scoreboard.h"
#include "sprites.h"

static int __score;
static int __score_best;

#define __SCOREBOARD_NO_DIGITS 3

void scoreboard_init(entity_t *e)
{
    __score = 0;
    __score_best = 0;
    for (size_t i=0; i<SCOREBOARD_NO_ENTITIES; i++) {
        e[i].rx = SPRITES_SCOREBOARD_WIDTH/2;
        e[i].ry = SPRITES_SCOREBOARD_HEIGHT/2;
        e[i].x = SCREEN_WIDTH - 4*(i%3+0.5f)*e[i].rx;
        e[i].y = 0.5f*e[i].rx + 4*(i/3+0.5f)*e[i].ry;
        e[i].entity_type = ENTITY_PIPE;
        e[i].tx_data.tx = sprites_load_scoreboard();
        e[i].active = true;
    }
}

static void __scoreboard_update(entity_t *e)
{
    e[0].tx_data.idx = __score%10;
    e[1].tx_data.idx = (__score/10)%10;
    e[2].tx_data.idx = (__score/100)%10;
}

void scoreboard_update(entity_t *e)
{
    __score++;
    __scoreboard_update((e + __SCOREBOARD_NO_DIGITS));
}

void scoreboard_reset(entity_t *e)
{
    if (__score > __score_best) {
        __scoreboard_update(e);
        __score_best = __score;
    }
    __score = 0;
    __scoreboard_update((e + __SCOREBOARD_NO_DIGITS));
}