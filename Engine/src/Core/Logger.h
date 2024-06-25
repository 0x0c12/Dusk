#pragma once

#include "Defines.h"

// Defining switches for log levels
#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disabling Debug level logs if release mode is on
#if DSK_RELEASE == 1
    #define LOG_DEBUG_ENABLED 0
    #define LOG_TRACE_ENABLED 0
#endif

// Log levels
typedef enum log_level {
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5
} log_level;

// Logger Functions
b8 DskInitialiseLogging();
void DskShutdownLogging();

void DSK_API DskLogOutput(log_level level, const char* message, ...);

// Logging macros
#define DSK_FATAL(message, ...) DskLogOutput(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

#ifndef DSK_ERROR
    #define DSK_ERROR(message, ...) DskLogOutput(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
    #define DSK_WARN(message, ...) DskLogOutput(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
    #define DSK_WARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
    #define DSK_INFO(message, ...) DskLogOutput(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
    #define DSK_INFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
    #define DSK_DEBUG(message, ...) DskLogOutput(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
    #define DSK_DEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
    #define DSK_TRACE(message, ...) DskLogOutput(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
    #define DSK_TRACE(message, ...)
#endif