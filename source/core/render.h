#pragma once
#include "entity.h"
#include "sprites.h"
#include "tx_kirby.h"
#include "level.h"

#include <gl2d.h>

static int PaletteID;
static int OriginalPaletteID;
// Make an all-white palette for stencil effects

void render_init()
{
    unsigned short hitPal[256];
    for(int i = 0; i < 256; i++ )
    {
        hitPal[i] = (0xFF << 8 ) | 0xFF;
    }
    
    glGenTextures(1, &PaletteID);
    glBindTexture(0, PaletteID);
    glColorTableEXT(0,0,256,0,0,hitPal);

    glGenTextures(1, &OriginalPaletteID);
    glBindTexture(0, OriginalPaletteID);
    glColorTableEXT(0,0,256,0,0,tx_kirbyPal);
}


void render(entity_t *entities[], int n)
{
    glBegin2D();

    entity_t *e;
    for (int i=0; i<n; i++)
    {
        e = entities[i];

        if ((g_gamestate == HIT) && ((e->entity_type == ENTITY_BG)||(e->entity_type == ENTITY_FG))) {
            int color = (hit_timeout) & 31;
			glColor( RGB15(color, color, color) );
        }
        if ((g_gamestate == HIT) && ((e->entity_type == ENTITY_PLAYER)||(e->entity_type == ENTITY_PIPE))) {
			glColor( RGB15(31,31,31) );
        } 
        
        if (e->active) {
            if (e->tx_data.rotation) {
                glSpriteOnQuad(
                    (int)(e->x - e->rx), (int)(e->y + e->ry),
                    (int)(e->x + e->rx), (int)(e->y + e->ry), 
                    (int)(e->x + e->rx), (int)(e->y - e->ry), 
                    (int)(e->x - e->rx), (int)(e->y - e->ry),
                    (int)e->tx_data.u, (int)e->tx_data.v,
                    e->tx_data.flip_mode, 
                    &e->tx_data.tx[e->tx_data.idx]
                );
            } else {
                glSpriteOnQuad(
                    (int)(e->x - e->rx), (int)(e->y - e->ry),
                    (int)(e->x - e->rx), (int)(e->y + e->ry), 
                    (int)(e->x + e->rx), (int)(e->y + e->ry), 
                    (int)(e->x + e->rx), (int)(e->y - e->ry), 
                    (int)e->tx_data.u, (int)e->tx_data.v,
                    e->tx_data.flip_mode, 
                    &e->tx_data.tx[e->tx_data.idx]
                );
            }
        }
    }
    glEnd2D();
    glFlush(0);

    swiWaitForVBlank();
}