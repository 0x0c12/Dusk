#include "Platform/Platform.h"

#ifdef DSK_PLATFORM_WINDOWS

    #include "Core/Logger.h"

    #include <windows.h>
    #include <windowsx.h>
    #include <stdlib.h>

    typedef struct internal_state
    {
        HINSTANCE h_instance;
        HWND h_wnd;
    } internal_state;

    // Clock
    static f64 clock_frequency;
    static LARGE_INTEGER start_time;

    LRESULT WINAPI Win32ProcessMessages(HWND h_wnd, u32 msg, WPARAM w_param, LPARAM l_param);

    // Lifetime functions implementations
    b8 PlatformStartup(
        platform_state* platform_state,
        const char* application_name,
        i32 x,
        i32 y,
        i32 width,
        i32 height)
    {
        // Setting up internal state of program and obtaining handle to application
        platform_state->internal_state = malloc(sizeof(internal_state));
        internal_state* state = (internal_state*)platform_state->internal_state;

        state->h_instance = GetModuleHandleA(0);

        // --- WINDOW SETUP --- //
        
        // Window Class Registration
        HICON icon = LoadIcon(state->h_instance, IDI_APPLICATION);
        WNDCLASSA wc;
        memset(&wc, 0, sizeof(WNDCLASSA));
        const char* wnd_class_name = "dusk_window_class";
        wc.style = CS_DBLCLKS;
        wc.lpfnWndProc = Win32ProcessMessages;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = state->h_instance;
        wc.hIcon = icon;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = NULL;
        wc.lpszClassName = wnd_class_name;

        if(!RegisterClassA(&wc))
        {
            MessageBoxA(0, "Window Class Registration failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
            return FALSE;
        }

        // Window Creation
        u32 client_x = x;
        u32 client_y = y;
        u32 client_width = width;
        u32 client_height = height;
        
        u32 window_x = client_x;
        u32 window_y = client_y;
        u32 window_width = client_width;
        u32 window_height = client_height;

        u32 window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
        u32 window_style_ex = WS_EX_APPWINDOW;

        window_style |= WS_MAXIMIZEBOX;
        window_style |= WS_MINIMIZEBOX;
        window_style |= WS_THICKFRAME;

        RECT border_rect = {0, 0, 0, 0};
        AdjustWindowRectEx(&border_rect, window_style, 0, window_style_ex);

        border_rect.left = window_x;
        border_rect.top = window_y;
        border_rect.right = window_x + window_width;
        border_rect.bottom = window_y + window_height;
        
        HWND wnd = CreateWindowExA(
            window_style_ex, wnd_class_name, application_name,
            window_style, window_x, window_y, window_width, window_height,
            0, 0, state->h_instance, 0);

        if(wnd == 0)
        {
            MessageBoxA(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

            DSK_FATAL("Window Creation Failed!");
            return FALSE;
        }
        else
        {
            state->h_wnd = wnd;
        }

        b32 should_activate = 1;
        i32 show_window_command_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;

        ShowWindow(state->h_wnd, show_window_command_flags);

        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        clock_frequency = 1.0 / (f64)frequency.QuadPart;
        QueryPerformanceCounter(&start_time);

        return TRUE;
    }

    void PlatformShutdown(platform_state* platform_state)
    {
        internal_state* state = (internal_state*)platform_state->internal_state;

        if(state->h_wnd)
        {
            DestroyWindow(state->h_wnd);
            state->h_wnd = 0;
        }
    }

    // Message Pump
    b8 PlatformPumpMessages(platform_state* platform_state)
    {
        MSG msg;
        while(PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        return TRUE;
    }

    // Memory functions implementations
    // TODO: Write custom memory allocators
    void* PlatformAllocate(u64 size, b8 aligned)
    {
        return malloc(size);
    }

    void PlatformFree(void* block, b8 aligned)
    {
        free(block);
    }
    
    void* PlatformZeroMemory(void* block, u64 size)
    {
        return memset(block, 0, size);
    }

    void* PlatformCopyMemory(void* dest, const void* source, u64 size)
    {
        return memcpy(dest, source, size);
    }

    void* PlatformSetMemory(void* dest, i32 value, u64 size)
    {
        return memset(dest, value, size);
    }

    void PlatformConsoleWrite(const char* message, u8 colour)
    {
        HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
        static u8 levels[6] = {64 | 8, 4, 6, 2, 1, 7};
        SetConsoleTextAttribute(console_handle, levels[colour]);
        OutputDebugStringA(message);
        u64 len = strlen(message);
        LPDWORD number_written = 0;
        WriteConsoleA(console_handle, message, (DWORD)len, number_written, 0);
    }

    void PlatformConsoleWriteError(const char* message, u8 colour)
    {
        HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
        static u8 levels[6] = {64 | 8, 4, 6, 2, 1, 7};
        SetConsoleTextAttribute(console_handle, levels[colour]);
        OutputDebugStringA(message);
        u64 len = strlen(message);
        LPDWORD number_written = 0;
        WriteConsoleA(console_handle, message, (DWORD)len, number_written, 0);
    }

    f64 PlatformGetAbsTime()
    {
        LARGE_INTEGER current_time;
        QueryPerformanceCounter(&current_time);
        return (f64)current_time.QuadPart * clock_frequency;
    }

    void PlatformSleep(u64 ms)
    {
        Sleep(ms);
    }

    LRESULT WINAPI Win32ProcessMessages(HWND h_wnd, u32 msg, WPARAM w_param, LPARAM l_param)
    {
        switch(msg)
        {
            case WM_ERASEBKGND:
            {
                return 1;
            } break;

            case WM_CLOSE:
            {
                // TODO: Call an event for the application to exit
                return 0;
            } break;
            case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;

            case WM_SIZE:
            {
                // TODO: Call an event for window resize
            } break;

            case WM_KEYDOWN:
            {
               // TODO: Input processing 
            } break;
            case WM_SYSKEYDOWN:
            {
               // TODO: Input processing 
            } break;
            case WM_KEYUP:
            {
               // TODO: Input processing 
            } break;
            case WM_SYSKEYUP:
            {
               // TODO: Input processing 
            } break;

            case WM_MOUSEMOVE:
            {
               // TODO: Input processing 
            } break;

            case WM_MOUSEWHEEL:
            {
                // TODO: Input processing
            } break;

            case WM_LBUTTONDOWN:
            {
                // TODO: Input processing
            } break;
            case WM_MBUTTONDOWN:
            {
                // TODO: Input processing
            } break;
            case WM_RBUTTONDOWN:
            {
                // TODO: Input processing
            } break;
            case WM_LBUTTONUP:
            {
                // TODO: Input processing
            } break;
            case WM_MBUTTONUP:
            {
                // TODO: Input processing
            } break;
            case WM_RBUTTONUP:
            {
                // TODO: Input processing
            } break;
        }

        return DefWindowProcA(h_wnd, msg, w_param, l_param);
    }

#endif