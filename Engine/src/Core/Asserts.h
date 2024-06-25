#pragma once

#include "Defines.h"

// Disable assertions by commenting following line
#define DSK_ASSERTIONS_ENABLED

#ifdef DSK_ASSERTIONS_ENABLED
    #if _MSC_VER
        #include <intrin.h>
        #define DebugBreak() __debugbreak()
    #else
        #define DebugBreak() __builtin_trap()
    #endif

    void DSK_API DskReportAssertionFailure(const char* expr, const char* msg, const char* file, i32 line);

    #define DSK_ASSERT(expr)                                                \
        {                                                                   \
            if(expr) {}                                                     \
            else                                                            \
            {                                                               \
                DskReportAssertionFailure(#expr, "", __FILE__, __LINE__);   \
                DebugBreak();                                               \
            }                                                               \
        }

    #define DSK_ASSERT_MSG(expr, msg)                                       \
        {                                                                   \
            if(expr) {}                                                     \
            else                                                            \
            {                                                               \
                DskReportAssertionFailure(#expr, msg __FILE__, __LINE__);   \
                DebugBreak();                                               \
            }                                                               \
        }
    
    #ifdef _DEBUG
        #define DSK_ASSERT_DBG(expr)                                            \
            {                                                                   \
                if(expr) {}                                                     \
                else                                                            \
                {                                                               \
                    DskReportAssertionFailure(#expr, "", __FILE__, __LINE__);   \
                    DebugBreak();                                               \
                }                                                               \
            }
    #else
        #define DSK_ASSERT_DBG(expr)
    #endif

#else
    #define DSK_ASSERT(expr)
    #define DSK_ASSERT_MSG(expr, msg)
    #define DSK_ASSERT_DBG(expr)
#endif