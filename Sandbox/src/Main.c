#include <Core/Logger.h>
#include <Core/Asserts.h>

#include <Platform/Platform.h>

int main(void)
{
    DSK_FATAL("Test message: %f", 28.08f);
    DSK_ERROR("Test message: %f", 28.08f);
    DSK_WARN("Test message: %f", 28.08f);
    DSK_INFO("Test message: %f", 28.08f);
    DSK_DEBUG("Test message: %f", 28.08f);
    DSK_TRACE("Test message: %f", 28.08f);

    platform_state state;
    if(PlatformStartup(&state, "Dusk Engine Test", 400, 100, 640, 480))
    {
        while(1)
        {
            PlatformPumpMessages(&state);
        }
    }

    PlatformShutdown(&state);

    return 0;
}
