#pragma once

#include "Defines.h"

typedef struct platform_state
{
    void* internal_state;
} platform_state;

// Lifetime functions
b8 DSK_API PlatformStartup(
    platform_state* platform_state,
    const char* application_Name,
    i32 x,
    i32 y,
    i32 width,
    i32 height);

void DSK_API PlatformShutdown(platform_state* platform_state);

// Message pump
b8 DSK_API PlatformPumpMessages(platform_state* platform_state);

// Platform specific memory functions
void* PlatformAllocate(u64 size, b8 aligned);
void PlatformFree(void* block, b8 aligned);
void* PlatformZeroMemory(void* block, u64 size);
void* PlatformCopyMemory(void* dest, const void* source, u64 size);
void* PlatformSetMemory(void* dest, i32 value, u64 size);

// Console logging functions
void PlatformConsoleWrite(const char* message, u8 colour);
void PlatformConsoleWriteError(const char* message, u8 colour);

f64 PlatformGetAbsTime();

void PlatformSleep(u64 ms);