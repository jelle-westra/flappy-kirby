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


	// initializing the entity systems
	kirby_init(&kirby);
	pipes_init(pipes);

	// keeping a list of all entities such that they can be rendered together
	entities[0] = &kirby;
	for (size_t j=0; j<PIPES_NO_ENTITIES; j++) {
		entities[j+1] = &pipes[j];
	}
	collision_init();

	iprintf("Hello from Jelle 123");

	while(pmMainLoop()) 
	{
		scanKeys();
		g_frame++;
		g_input = keysDown();

		iprintf("\x1b[10;0Hframe = %d; %d", g_frame, g_gamestate);



		// MENU is only triggered after a game over
		if (g_gamestate != MENU) {
			// update entities
			kirby_update(&kirby);
			pipes_update(pipes);
			// env_update(env);
			
			// check collision
			if (g_gamestate == PLAY) {
				// will put the gamemode in OVER when kirby collides pipes
				collision_update(&kirby, pipes);
			}

		} else {
			// menu_update();
			iprintf("dit is het menu");

			if (g_input & KIRBY_KEY_JUMP) {
				g_gamestate = RESET;
				// pipes_reset(pipes);
			}
		}
		render(entities, LEVEL_NO_ENITITES);
	}
	return 0;
}
