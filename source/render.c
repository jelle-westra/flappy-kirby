#include "render.h"

#include "core/state.h"
#include "entity.h"
#include "level.h"

#include <nds.h>
#include <gl2d.h>

void render(entity_t *entities[])
{
    glBegin2D();

    entity_t *e;
    for (int i=0; i<LEVEL_NO_ENITITES; i++)
    {
        e = entities[i];

        if ((g_gamestate == HIT) && ((e->entity_type == ENTITY_BG)||(e->entity_type == ENTITY_FG))) {
            int color = (e->tx_data.frame) & 31;
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