#include "Core/Logger.h"
#include "Core/Asserts.h"

// Temporary, Remove when platform layer is build
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void DskReportAssertionFailure(const char* expr, const char* msg, const char* file, i32 line)
{
    DskLogOutput(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expr, msg, file, line);
}

b8 DskInitialiseLogging()
{
    return TRUE;
}

void DskShutdownLogging()
{
    // TODO: Queue cleanup process alongwith file-write stage of logging
}

void DskLogOutput(log_level level, const char* message, ...)
{
    const char* level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    // b8 is_error = level < 2;

    char out_message[32000];
    memset(out_message, 0, sizeof(out_message));

    va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);

    char out_message2[32000];
    sprintf(out_message2, "%s%s\n", level_strings[level], out_message);

    // TODO: Platform specific output
    printf("%s", out_message2);
}