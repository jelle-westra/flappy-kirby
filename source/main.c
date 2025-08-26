#include <nds.h>
#include <stdio.h>
#include <gl2d.h>


// #include "tiles.h"
// #include "logo.h"

#include "core/state.h"
#include "core/render.h"
#include "kirby.h"

glImage tx_tiles[1];
// const unsigned int texcoords_bg[] = {
	// 	0, 0, 256, 192,
	// };
	
#define NO_PIPES 6
#define NO_ENV 0
#define NO_ENTITIES 1+NO_PIPES+NO_ENV
	
gamestate_t g_gamestate = IDLE;
uint32_t g_frame = 0;
uint32_t g_input = 0;

entity_t kirby;
entity_t pipes[NO_PIPES];

entity_t *entities[NO_ENTITIES];


int main(void) 
{
	videoSetMode(MODE_5_3D);
	consoleDemoInit();	
	glScreen2D();
	vramSetBankA(VRAM_A_TEXTURE);
	vramSetBankE(VRAM_E_TEX_PALETTE);


	kirby_init(&kirby);

	entities[0] = &kirby;
	// pipes_init(pipes, NO_PIPES);

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
		g_frame++;
		g_input = keysDown();

		kirby_update(&kirby);
		// pipes_handler(pipes);
		// env_handler(env);

		render(entities, 1);
	}
	return 0;
}
