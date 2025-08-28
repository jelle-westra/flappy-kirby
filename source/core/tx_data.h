#pragma once
#include <gl2d.h>

typedef enum
{
    TX_ROT_NONE,
    TX_ROT_90
} tx_rotation_t;

typedef struct
{
    glImage *tx;
    GL_FLIP_MODE flip_mode;
    tx_rotation_t rotation;
    float u;
    float v;
	uint8_t frame, idx;
} tx_data_t;
