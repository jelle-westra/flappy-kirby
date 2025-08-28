#pragma once
#include <gl2d.h>

#define SPRITES_FG_WIDTH SCREEN_WIDTH
#define SPRITES_FG_HEIGHT 32

#define SPRITES_BG_WIDTH SCREEN_WIDTH
#define SPRITES_BG_HEIGHT SCREEN_HEIGHT

#define SPRITES_PIPE_WIDTH 128
#define SPRITES_PIPE_HEIGHT 32

extern int sprites_kirby_id;

glImage* sprites_load_kirby();
glImage* sprites_load_pipes();
glImage* sprites_load_bg();
glImage* sprites_load_fg();