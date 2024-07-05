#include "Game.h"

#include <Startup.h>

// TODO: Remove ASAP
#include <Platform/Platform.h>

b8 CreateGame(Game* out_game)
{
    out_game->app_config.start_pos_x = 100;
    out_game->app_config.start_pos_y = 100;
    out_game->app_config.start_width = 640;
    out_game->app_config.start_height = 480;
    out_game->app_config.name = "Dusk Test Window";

    out_game->Initialise = GameInitialise;
    out_game->Update = GameUpdate;
    out_game->Render = GameRender;
    out_game->OnResize = GameOnResize;

    out_game->state = PlatformAllocate(sizeof(GameState), FALSE);

    return TRUE;
}