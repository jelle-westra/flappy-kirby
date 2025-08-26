#include <nds.h>
#include <stdio.h>
#include <gl2d.h>


// #include "tiles.h"
// #include "logo.h"

#include "core/state.h"
#include "core/render.h"

#include "level.h"
#include "kirby.h"
#include "pipes.h"

glImage tx_tiles[1];
// const unsigned int texcoords_bg[] = {
	// 	0, 0, 256, 192,
	// };
	

	
gamestate_t g_gamestate = IDLE;
uint32_t g_frame = 0;
uint32_t g_input = 0;

entity_t kirby;
entity_t pipes[PIPES_NO_ENTITIES];

entity_t *entities[LEVEL_NO_ENITITES];


int main(void) 
{
	videoSetMode(MODE_5_3D);
	consoleDemoInit();	
	glScreen2D();
	vramSetBankA(VRAM_A_TEXTURE);
	vramSetBankE(VRAM_E_TEX_PALETTE);


	kirby_init(&kirby);
	pipes_init(pipes);

	// keeping a list of all entities such that they can be rendered together
	entities[0] = &kirby;
	for (size_t j=0; j<PIPES_NO_ENTITIES; j++) {
		entities[j+1] = &pipes[j];
	}

	// env entities, background and foreground

	// glLoadSpriteSet(
	// 	tx_bg, 1, texcoords_bg,
	// 	GL_RGB256, TEXTURE_SIZE_256, TEXTURE_SIZE_256,
	// 	GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_OFF|GL_TEXTURE_COLOR0_TRANSPARENT,
	// 	256,
	// 	(u16*)drunkenlogoPal,
	// 	(u8*)drunkenlogoBitmap
	// );

	


	iprintf("Hello from Jelle 123");

	while(pmMainLoop()) 
	{
		scanKeys();
		g_frame++;
		g_input = keysDown();

		iprintf("\x1b[10;0Hframe = %d; %d; %d", g_frame, (int)pipes[0].x, (int)pipes[0].y);

		// MENU is only triggered after a game over
		if (g_gamestate != MENU) {
			kirby_update(&kirby);
			pipes_update(pipes);
			// env_update(env);
	
		} else {
			// menu_update();
			iprintf("dit is het menu");
		}
		render(entities, LEVEL_NO_ENITITES);
	}
	return 0;
}
