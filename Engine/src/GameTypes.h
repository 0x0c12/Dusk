#pragma once

#include "Core/Application.h"

typedef struct Game
{
    application_config app_config;

    b8 (*Initialise)(struct Game* game_instance);
    b8 (*Update)(struct Game* game_instance, f32 delta_time);
    b8 (*Render)(struct Game* game_instance, f32 delta_time);
    void (*OnResize)(struct Game* game_instance, u32 width, u32 height);

    void* state;
} Game;