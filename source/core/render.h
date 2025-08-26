#pragma once
#include "entity.h"

#include <gl2d.h>

void render(entity_t *entities[], int n)
{
    glBegin2D();

    entity_t *e;
    for (int i=0; i<n; i++)
    {
        e = entities[i];
        
        if (e->active) {
            if (e->entity_type == ENTITY_PIPE) {
                glBoxFilled(
                    (int)(e->x - e->rx),
                    (int)(e->y - e->ry),
                    (int)(e->x + e->rx),
                    (int)(e->y + e->ry),
                    255
                );
                continue;
            } 
            glSprite(
                (int)(e->x - e->rx), 
                (int)(e->y - e->ry), 
                GL_FLIP_NONE, 
                &e->tx_data.tx[e->tx_data.idx]
            );
        }
    }
    glEnd2D();
    glFlush(0);

    swiWaitForVBlank();
}