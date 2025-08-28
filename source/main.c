#include <nds.h>
#include <stdio.h>
#include <gl2d.h>

#include "core/state.h"
#include "core/render.h"

#include "level.h"
#include "kirby.h"
#include "pipes.h"
#include "scoreboard.h"

entity_t kirby;
entity_t pipes[PIPES_NO_ENTITIES];
entity_t env[ENV_NO_ENTITIES];
entity_t scoreboard[SCOREBOARD_NO_ENTITIES];

entity_t *entities[LEVEL_NO_ENITITES];

int main(void) 
{
	// initialize video and console
	videoSetMode(MODE_5_3D);
	consoleDemoInit();	
	glScreen2D();
	vramSetBankA(VRAM_A_TEXTURE);
	vramSetBankE(VRAM_E_TEX_PALETTE);

	// initializing the entity systems
	kirby_init(&kirby);
	pipes_init(&pipes[0]);
	env_init(&env[0]);
	scoreboard_init(&scoreboard[0]);

	// keeping a list of all entities such that they can be rendered together
	for (size_t i=0; i<ENV_NO_ENTITIES; i++) {
		entities[i] = &env[i];
	}
	for (size_t i=0; i<PIPES_NO_ENTITIES; i++) {
		entities[ENV_NO_ENTITIES + i] = &pipes[i];
	}
	for (size_t i=0; i<SCOREBOARD_NO_ENTITIES; i++) {
		entities[PIPES_NO_ENTITIES + ENV_NO_ENTITIES + i] = &scoreboard[i];
	}
	entities[SCOREBOARD_NO_ENTITIES + PIPES_NO_ENTITIES + ENV_NO_ENTITIES] = &kirby;

	state_init();
	level_init();
	render_init();

	while(pmMainLoop()) 
	{
		state_update();
		iprintf("\x1b[10;0Hframe = %d; %d", g_frame);

		// MENU is only triggered after a game over
		if (g_gamestate != MENU) {
			// update entities physics and animation
			kirby_update(&kirby);
			pipes_update(&pipes[0]);
			env_update(&env[0]);

			// update game logic (collision check is done in level_update)
			level_update(&kirby, &pipes[0], &scoreboard[0]);

		} else {
			// menu_update();
			// iprintf("dit is het menu");

			// wainting for jump to start the game
			if (g_input & KIRBY_KEY_JUMP) {
				state_reset();
				level_reset();
				scoreboard_reset(&scoreboard[0]);
			}
		}
		render(entities, LEVEL_NO_ENITITES);
	}
	kirby_destroy(&kirby);
	pipes_destroy(&pipes[0]);
	return 0;
}
