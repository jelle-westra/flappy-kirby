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
        glSprite(
            e->x, 
            e->y, 
            GL_FLIP_NONE, 
            &e->tx_data.tx[e->tx_data.frame]
        );
    }
    glEnd2D();
    glFlush(0);

    swiWaitForVBlank();
}