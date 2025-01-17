#pragma once

// Unsigned int Defines
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// Signed int Defines
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

// Floating point types
typedef float f32;
typedef double f64;

// Bool types
typedef char b8;
typedef int b32;

// Defining static assertions
#if defined(__clang__) || defined(__gcc__)
    #define STATIC_ASSERT _Static_assert
#else
    #define STATIC_ASSERT static_assert
#endif

// Type-size checking
STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be of 1 byte");
STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be of 2 bytes");
STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be of 4 bytes");
STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be of 8 bytes");

STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be of 1 byte");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be of 2 bytes");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be of 4 bytes");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be of 8 bytes");

STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be of 4 bytes");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be of 8 bytes");

#define TRUE 1
#define FALSE 0

// Platform Detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define DSK_PLATFORM_WINDOWS 1
    #ifndef _WIN64
        #error "64-bit is required to run on Windows!"
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    #define DSK_PLATFORM_LINUX 1
#else
    #error "Unsupported platform!"
#endif

#ifdef DSK_EXPORT
    #ifdef _MSC_VER
        #define DSK_API __declspec(dllexport)
    #else
        #define DSK_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _MSC_VER
        #define DSK_API __declspec(dllimport)
    #else
        #define DKS_API
    #endif
#endif