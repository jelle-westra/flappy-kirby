#include "core/state.h"
#include "core/entity.h"
#include "sprites.h"

#include "kirby.h"
#include <gl2d.h>
#include <nds.h>

#include "tx_kirby.h"

#define KIRBY_SPRITE_HEIGHT KIRBY_SPRITE_WIDTH

#define KIRBY_NO_SPRITES 6
#define KIRBY_NO_FRAMES_ANIMATION 15

#define KIRBY_GRAVITY .125f
#define KIRBY_BOOST -2.6f
#define KIRBY_BOUNCE_COEFFICIENT 0.6f

#define KIRBY_MAX_HEIGHT 0.f
#define KIRBY_MIN_HEIGHT SCREEN_HEIGHT - 40

// u, v, width, height
const unsigned int kirby_texcoords[] = {
	0,0,33,32,
	33,0,33,32,
	66,0,33,32,
	99,0,33,32,
	132,0,33,32,
	165,0,33,32
};

static const uint8_t kirby_animation[KIRBY_NO_FRAMES_ANIMATION] = {
	3,3,3,
	4,4,4,
	5,5,5,
	4,4,4,
	3,3,3
};

void kirby_init(entity_t *e)
{
	e->active = true;
	e->x = KIRBY_X; 
	e->y = KIRBY_Y;
	e->vx = 0;
	e->vy = 0;
	e->rx = KIRBY_SPRITE_WIDTH/2;
	e->ry = KIRBY_SPRITE_HEIGHT/2;
	e->entity_type = ENTITY_PLAYER;
	
	e->tx_data.tx = sprites_load_kirby();
	e->tx_data.frame = 0;
	e->tx_data.idx = 0;
}

static void kirby_jump(entity_t *e)
{
	e->vy = KIRBY_BOOST;
	e->tx_data.frame = 0;
}

void kirby_update(entity_t *e)
{	
	// [Logic]
	switch (g_gamestate)
	{
		case IDLE:
			if (g_input&KIRBY_KEY_JUMP) {
				g_gamestate=PLAY;
				kirby_jump(e);
			} else if (e->y > SCREEN_HEIGHT/2) {
				kirby_jump(e);
			}
			break;
		case PLAY:
			// kirby is controllable
			if (g_input&KIRBY_KEY_JUMP) kirby_jump(e);
			break;
		case HIT:
			break;
		case OVER:
			// kirby is uncontrollable and will bounce off the floor
			break;
		case RESET:
			// rising to the IDLE state
			if (e->y > SCREEN_HEIGHT/2) {
				kirby_jump(e);
			}
		default:
			break;
	}
	if (g_gamestate != HIT) {
		if (e->y >= KIRBY_MIN_HEIGHT && e->vy > 0.f) {
			// if it exceeds the floor and still falls we swap the direction and take some energy
			e->vy = -KIRBY_BOUNCE_COEFFICIENT*e->vy;
			e->tx_data.frame = 0;
		}
		e->vy += KIRBY_GRAVITY;
		e->y += e->vy;

		if (e->y < KIRBY_MAX_HEIGHT) {
			e->y = KIRBY_MAX_HEIGHT;
		} 
		if (e->y > KIRBY_MIN_HEIGHT) {
			e->y = KIRBY_MIN_HEIGHT;
		}
		
		// [Animation]
		if (e->tx_data.frame < KIRBY_NO_FRAMES_ANIMATION)
		{	// jump animation
			e->tx_data.idx = kirby_animation[e->tx_data.frame];
		} 
		else 
		{	// fall animation; based on the speed kirby falls
			e->tx_data.idx = (e->vy > 3.f) ? (e->tx_data.frame)%12/4 : (e->tx_data.frame)%24/8;
		}
		e->tx_data.frame++;
	}
}

void kirby_destroy(entity_t *e)
{
	if (e->tx_data.tx) {
        free(e->tx_data.tx);
		e->tx_data.tx = NULL;
    }
}