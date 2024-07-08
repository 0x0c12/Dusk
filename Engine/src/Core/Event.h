#pragma once

#include "Defines.h"

typedef struct event_context
{
    union
    {
        i64 i64[2];
        u64 u64[2];
        f64 f64[2];

        i32 i32[4];
        u32 u32[4];
        f32 f32[4];

        i16 i16[8];
        u16 u16[8];

        i8 i8[16];
        u8 u8[16];

        char c[16];
    } data;
} event_context;

typedef b8 (*PFNOnEvent)(u16 code, void* speaker, void* listener_instance, event_context data);

// Event Lifetime functions
b8 EventInitialised();
void EventShutdown();

DSK_API b8 EventRegister(u16 code, void* listener, PFNOnEvent on_event);
DSK_API b8 EventUnregister(u16 code, void* listener, PFNOnEvent on_event);

DSK_API b8 EventAnnounce(u16 code, void* speaker, event_context context);

typedef enum system_event_code
{
    EVENT_CODE_APPLICATION_QUIT = 0x01,

    /* Context Usage:
     * u16 key_code = data.data.u16[0];
     */
    EVENT_CODE_KEY_PRESSED = 0x02,

    /* Context Usage:
     * u16 key_code = data.data.u16[0];
     */
    EVENT_CODE_KEY_RELEASED = 0x03,

    /* Context Usage:
     * u16 button = data.data.u16[0];
     */
    EVENT_CODE_BUTTON_PRESSED = 0x04,

    /* Context Usage:
     * u16 button = data.data.u16[0];
     */
    EVENT_CODE_BUTTON_RELEASED = 0x05,

    /* Context Usage:
     * u16 x = data.data.u16[0];
     * u16 y = data.data.u16[1];
     */
    EVENT_CODE_MOUSE_MOVED = 0x06,

    /* Context Usage:
     * u16 z_delta = data.data.u8[0];
     */
    EVENT_CODE_MOUSE_WHEEL = 0x07,

    /* Context Usage:
     * u16 width = data.data.u16[0];
     * u16 height = data.data.u16[1];
     */
    EVENT_CODE_WND_RESIZE = 0x08,

    MAX_EVENT_CODE = 0xFF
} system_event_code;