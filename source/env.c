#include "core/state.h"
#include "env.h"
#include "level.h"

#include "tx_env.h"

#include "sprites.h"

#define SPRITE_ENV_WIDTH SCREEN_WIDTH
#define SPRITE_ENV_HEIGHT SCREEN_HEIGHT
#define SPRITE_ENV_NO_SPRITES 1

#define __SPEED (e[i].entity_type == ENTITY_FG) ? LEVEL_SPEED_FG : LEVEL_SPEED_BG
#define __DECELL_FAC (e[i].entity_type == ENTITY_BG) ? LEVEL_SPEED_BG/LEVEL_SPEED_FG : 1.f

const unsigned int texcoords_bg[] = {
    0, 0, SPRITE_ENV_WIDTH, SPRITE_ENV_HEIGHT,
};

void env_init(entity_t *e)
{
    e[0].active = true;
    e[0].x = (float)SPRITES_BG_WIDTH/2.f;
    e[0].y = (float)SPRITES_BG_HEIGHT/2.f;
    e[0].rx = (float)SPRITES_BG_WIDTH/2.f;
    e[0].ry = (float)SPRITES_BG_HEIGHT/2.f;
    e[0].entity_type = ENTITY_BG;

    e[1].active = true;
    e[1].x = (float)SPRITES_FG_WIDTH/2.f;
    e[1].y = SCREEN_HEIGHT - (float)SPRITES_FG_HEIGHT/2.f;
    e[1].rx = (float)SPRITES_FG_WIDTH/2.f;
    e[1].ry = (float)SPRITES_FG_HEIGHT/2.f;
    e[1].entity_type = ENTITY_FG;

	e[0].tx_data.tx = sprites_load_bg();
	e[1].tx_data.tx = sprites_load_fg();
}

void env_update(entity_t *e)
{
    for (size_t i=0; i<ENV_NO_ENTITIES; i++) {
        switch (g_gamestate)
        {
        case IDLE:
            e[i].vx = __SPEED;
            break;
        case PLAY:
            e[i].vx = __SPEED;
            break;
        case HIT:
            e[i].tx_data.frame++;
            break;
            case OVER:
            e[i].vx += LEVEL_SPEED_OVER_DECELLERATION;
            if (e[i].vx > 0.f) {
                e[i].vx = 0.f; 
            }
            break;
            case RESET:
            e[i].vx -= LEVEL_SPEED_OVER_DECELLERATION * __DECELL_FAC;
            if (e[i].vx < __SPEED) {
                e[i].vx = __SPEED; 
            }
            e[i].tx_data.frame = 0;
        default:
            break;
        }
        if (g_gamestate != HIT) {
            e[i].tx_data.u -= e[i].vx;
            if (e[i].tx_data.u < SCREEN_WIDTH) e[i].tx_data.u += SCREEN_WIDTH;
        }
    }
}

void env_destroy(entity_t *e)
{

}
