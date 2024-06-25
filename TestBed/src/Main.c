#include <Core/Logger.h>
#include <Core/Asserts.h>

int main(void)
{
    DSK_FATAL("Test message: %f", 6.28f);
    DSK_ERROR("Test message: %f", 6.28f);
    DSK_WARN("Test message: %f", 6.28f);
    DSK_INFO("Test message: %f", 6.28f);
    DSK_DEBUG("Test message: %f", 6.28f);
    DSK_TRACE("Test message: %f", 6.28f);

    return 0;
}