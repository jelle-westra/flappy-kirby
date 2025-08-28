#include "sprites.h"

#include "tx_kirby.h"
#include "tx_env.h"

#define SPRITES_KIRBY_NO_SPRITES 6

#define SPRITES_FG_NO_SPRITES 1
#define SPRITES_BG_NO_SPRITES 1
#define SPRITES_PIPE_NO_SPRITES 2

#define SPRITES_ENV_NO_SPRITES (SPRITES_FG_NO_SPRITES + SPRITES_BG_NO_SPRITES + SPRITES_PIPE_NO_SPRITES)

static glImage __sprites_kirby[SPRITES_KIRBY_NO_SPRITES];
static bool __sprites_kirby_loaded = false;

int sprites_kirby_id = 0;


static const unsigned int __sprites_texcoords_env[] = {
    0, 192, SPRITES_FG_WIDTH, SPRITES_FG_HEIGHT, // foreground
    0, 0, SPRITES_BG_WIDTH, SPRITES_BG_HEIGHT, // background
    0, 160, 128, 32, // pipe 1
    128, 160, 128, 32, // pipe 2
};

static glImage __sprites__env[SPRITES_ENV_NO_SPRITES];
static bool __sprites_env_loaded = false;

glImage *sprites_load_kirby()
{
    if (!__sprites_kirby_loaded) {
        sprites_kirby_id = glLoadTileSet( 
            __sprites_kirby,
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
        __sprites_kirby_loaded = true;
    }
    return __sprites_kirby;
}

static void __sprites_load_env()
{
    if (!__sprites_env_loaded) {
        glLoadSpriteSet(
            __sprites__env, SPRITES_ENV_NO_SPRITES, __sprites_texcoords_env, 
            GL_RGB256, TEXTURE_SIZE_256, TEXTURE_SIZE_256, 
            GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_OFF|GL_TEXTURE_COLOR0_TRANSPARENT,
            256, (u16*)tx_envPal, (u8*)tx_envBitmap
        );
        __sprites_env_loaded = true;
    }
}

glImage *sprites_load_fg()
{
    __sprites_load_env();
    return (__sprites__env);
}

glImage *sprites_load_bg()
{
    __sprites_load_env();
    return (__sprites__env + SPRITES_FG_NO_SPRITES);
}

glImage *sprites_load_pipes()
{
    __sprites_load_env();
    return (__sprites__env + SPRITES_FG_NO_SPRITES + SPRITES_BG_NO_SPRITES);
}
