#include "Application.h"
#include "GameTypes.h"

#include "Core/Logger.h"

#include "Platform/Platform.h"
#include "Core/DskMemory.h"

typedef struct application_state
{
    Game* game_instance;
    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    i16 width;
    i16 height;
    f64 last_time;
} application_state;

static b8 initialised = FALSE;
static application_state app_state;

b8 ApplicationInit(Game* game_instance)
{
    if(initialised)
    {
        DSK_ERROR("ApplicationInit() called more than once!");
        return FALSE;
    }

    app_state.game_instance = game_instance;

    // --- Initialisation of Subsystems --- //

    DskInitialiseLogging();

    // TODO: Test code
    DSK_FATAL("Test message: %f", 28.08f);
    DSK_ERROR("Test message: %f", 28.08f);
    DSK_WARN("Test message: %f", 28.08f);
    DSK_INFO("Test message: %f", 28.08f);
    DSK_DEBUG("Test message: %f", 28.08f);
    DSK_TRACE("Test message: %f", 28.08f);

    // --- end --- //

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    if(!PlatformStartup(&app_state.platform, game_instance->app_config.name,
                       game_instance->app_config.start_pos_x, game_instance->app_config.start_pos_y,
                       game_instance->app_config.start_width, game_instance->app_config.start_height))
    {
        return FALSE;
    }

    if(!app_state.game_instance->Initialise(app_state.game_instance))
    {
        DSK_FATAL("Game failed to initialise");
        return FALSE;
    }

    app_state.game_instance->OnResize(app_state.game_instance, app_state.width, app_state.height);

    initialised = TRUE;

    return TRUE;
}

b8 ApplicationRun()
{
    while(app_state.is_running)
    {
        if(!PlatformPumpMessages(&app_state.platform))
            app_state.is_running = FALSE;
        
        if(!app_state.is_suspended)
        {
            if(!app_state.game_instance->Update(app_state.game_instance, (f32)0))
            {
                DSK_FATAL("Game update failed. Shutting down!");
                app_state.is_running = FALSE;
                break;
            }

            if(!app_state.game_instance->Render(app_state.game_instance, (f32)0))
            {
                DSK_FATAL("Game render failed. Shutting down!");
                app_state.is_running = FALSE;
                break;
            }
        }
    }

    app_state.is_running = FALSE;

    PlatformShutdown(&app_state.platform);

    return TRUE;
}