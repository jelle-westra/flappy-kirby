#pragma once
#include "stdbool.h"
#include "tx_data.h"

typedef enum 
{
    ENTITY_PLAYER,
    ENTITY_PIPE,
    ENTITY_BG,
    ENTITY_FG,
} entity_type_t;

typedef struct
{
    float x, y;   // position (center)
    float vx, vy; // velocity
    float rx, ry; // radius
    bool active;
    entity_type_t entity_type;
    tx_data_t tx_data;
} entity_t;