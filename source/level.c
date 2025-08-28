#include "core/state.h"
#include "level.h"
#include "kirby.h"

#include <stdio.h>

int hit_timeout;

static size_t __pipe_collider_idx;
static int __score;

void level_init()
{
    level_reset();
}   

void level_reset()
{
    __pipe_collider_idx = 0;
    __score = 0;
    hit_timeout = 0;
}

static bool __collision_check(const entity_t *kirby, const entity_t *pipe)
{
    // written using ChatGPT: find closest point on rect to circle center
    float x_closest = (kirby->x < pipe->x + pipe->rx) ? 
                    ((kirby->x > pipe->x - pipe->rx) ? kirby->x : pipe->x - pipe->rx) 
                    : pipe->x + pipe->rx;
    float y_closest = (kirby->y < pipe->y + pipe->ry) ? 
                    ((kirby->y > pipe->y - pipe->ry) ? kirby->y : pipe->y - pipe->ry) 
                    : pipe->y + pipe->ry;

    // distance from circle center to this point
    float dx = kirby->x - x_closest;
    float dy = kirby->y - y_closest;

    return (dx*dx + dy*dy) <= (KIRBY_COLLIDER_RADIUS*KIRBY_COLLIDER_RADIUS);
}

void level_update(entity_t *kirby, entity_t pipes[])
{
    switch (g_gamestate)
    {
    case IDLE:
        break;
    case PLAY:
        if (pipes[__pipe_collider_idx].x < kirby->x-KIRBY_SPRITE_WIDTH) {
            // __pipe_collider_idx = (__pipe_collider_idx+2)%PIPES_NO_ENTITIES;
            __pipe_collider_idx += 2;
            if (__pipe_collider_idx >= PIPES_NO_ENTITIES) {
                __pipe_collider_idx = 0;
            }
            __score++;
            iprintf("score: %d", __score);
        }
        if (
            __collision_check(kirby, &pipes[__pipe_collider_idx]) ||
            __collision_check(kirby, &pipes[__pipe_collider_idx + 1])
        ) {
            // TODO : set color palettes
            g_gamestate = HIT;
        }
        break;
        case HIT:
        // TODO : set color palettes
        if (hit_timeout++ > 10) {
            g_gamestate = OVER;
        }
        break;
    default:
        break;
    }
}
