#include "core/state.h"
#include "level.h"
#include "kirby.h"

static size_t __pipe_collider_idx;

void collision_init()
{
    __pipe_collider_idx = 0;   
}

static bool __collision_check(const entity_t *kirby, const entity_t *pipe)
{
    // written using ChatGPT: find closest point on rect to circle center
    float x_closest = (KIRBY_X < pipe->x + pipe->rx) ? 
                    ((KIRBY_X > pipe->x - pipe->rx) ? KIRBY_X : pipe->x - pipe->rx) 
                    : pipe->x + pipe->rx;
    float y_closest = (kirby->y < pipe->y + pipe->ry) ? 
                    ((kirby->y > pipe->y - pipe->ry) ? kirby->y : pipe->y - pipe->ry) 
                    : pipe->y + pipe->ry;

    // distance from circle center to this point
    float dx = KIRBY_X - x_closest;
    float dy = kirby->y - y_closest;

    return (dx*dx + dy*dy) <= (KIRBY_COLLIDER_RADIUS*KIRBY_COLLIDER_RADIUS);
}

void collision_update(entity_t *kirby, entity_t pipes[])
{
    if (pipes[__pipe_collider_idx].x < KIRBY_X-KIRBY_SPRITE_WIDTH) {
        __pipe_collider_idx = (__pipe_collider_idx+2)%PIPES_NO_ENTITIES;
    }
    if (
        __collision_check(kirby, &pipes[__pipe_collider_idx]) ||
        __collision_check(kirby, &pipes[__pipe_collider_idx + 1])
    ) {
        g_gamestate = OVER;
    }
}
