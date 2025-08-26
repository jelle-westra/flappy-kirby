#include "core/state.h"
#include "core/entity.h"

#include "kirby.h"
#include <gl2d.h>

#include "logo.h"
#include <stdio.h>

#include "tx_kirby.h"

#define KIRBY_NO_SPRITES 4
#define KIRBY_NO_FRAMES_ANIMATION 15
#define KIRBY_GRAVITY .125f
#define KIRBY_BOOST -2.6f

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
	e->x = SCREEN_WIDTH/3; 
	e->y = SCREEN_HEIGHT/2;
	e->vx = 0;
	e->vy = 0;
	
	glImage *tx = malloc(sizeof(glImage) * KIRBY_NO_SPRITES);
	
	glLoadTileSet( 
		tx,
		33,
		32,
		256,
		32,
		GL_RGB16,
		TEXTURE_SIZE_256,
		TEXTURE_SIZE_32,
		GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_OFF|GL_TEXTURE_COLOR0_TRANSPARENT,
		16,		// Just use 0 if palette is not in use
		(u16*)tx_kirbyPal,		// Just use 0 if palette is not in use
		(u8*)tx_kirbyBitmap
	);
	
	e->tx_data.tx = tx;
	e->tx_data.frame = 0;
}

void kirby_update(entity_t *e)
{
	iprintf("\x1b[10;0Hframe = %d; %f", g_frame, e->vy);

	e->y += e->vy;
	e->vy += KIRBY_GRAVITY;

	// [Logic]
	switch (g_gamestate)
	{
	case IDLE:
		if (e->y > SCREEN_HEIGHT/2)
		{
			e->vy = KIRBY_BOOST;
			e->tx_data.frame = 0;
		}
		break;
	case PLAY:
		// on input jump
		break;
	case OVER:
		// Fall down
		break;
	default:
		break;
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
	e->tx_data.frame += 1;
}

void kirby_destroy(entity_t *e)
{
	if (e->tx_data.tx) {
        free(e->tx_data.tx);
		e->tx_data.tx = NULL;
    }
}