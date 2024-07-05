#include "Game.h"

#include <Core/Logger.h>

b8 GameInitialise(Game* game_instance)
{
    DSK_DEBUG("GameInitialise() was called!");
    return TRUE;
}

b8 GameUpdate(Game* game_instance, f32 delta_time)
{
    return TRUE;
}

b8 GameRender(Game* game_instance, f32 delta_time)
{
    return TRUE;
}

void GameOnResize(Game* game_instance, u32 width, u32 height)
{
    DSK_DEBUG("Game Window was resized![GameOnResize() called]");
}