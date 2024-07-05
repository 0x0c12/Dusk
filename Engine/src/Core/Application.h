#pragma once

#include "Defines.h"

struct Game;

typedef struct application_config
{
    i16 start_pos_x;
    i16 start_pos_y;
    
    i16 start_width;
    i16 start_height;

    char* name;
} application_config;

b8 DSK_API ApplicationInit(struct Game* game_instance);
b8 DSK_API ApplicationRun();