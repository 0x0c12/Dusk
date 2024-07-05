#pragma once

#include <Defines.h>
#include <GameTypes.h>

typedef struct GameState
{
    f32 delta_time;
} GameState;

b8 GameInitialise(Game* game_instance);
b8 GameUpdate(Game* game_instance, f32 delta_time);
b8 GameRender(Game* game_instance, f32 delta_time);
void GameOnResize(Game* game_instance, u32 width, u32 height);
