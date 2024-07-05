#pragma once

#include "Core/Application.h"
#include "Core/Logger.h"
#include "GameTypes.h"

extern b8 CreateGame(Game* out_game);

// EntryPoint of application
int main(void)
{
    Game game_instance;

    if(!CreateGame(&game_instance))
    {
        DSK_FATAL("Could not read game!");
        return -1;
    }

    if(!game_instance.Render || !game_instance.Update || !game_instance.Initialise || !game_instance.OnResize)
    {
        DSK_FATAL("The function pointers must be assigned");
        return -2;
    }

    if(!ApplicationInit(&game_instance))
    {
        DSK_FATAL("Failed to create application");
        return 1;
    }

    if(!ApplicationRun()) {
        DSK_INFO("The application failed to shutdown properly.");
        return 2;
    }

    return 0;
}