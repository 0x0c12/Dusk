@ECHO OFF
REM Build file for Engine(Dynamic Link Library - DLL)
SetLocal EnableDelayedExpansion

REM Snippet to fetch all .c files
SET c_filenames=
FOR /R %%f in (*.c) do (
    SET c_filenames=!c_filenames! %%f
)

REM Flags and arguments
SET target=Engine
SET c_flags=-g -shared -Wvarargs -Wall -Werror
SET inc_flags=-Isrc -I%VULKAN_SDK%/Include
SET lnk_flags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib
SET defines=-D_DEBUG -DDSK_EXPORT -D_CRT_SECURE_NO_WARNINGS

REM Actual build process
ECHO "Building %target%%..."
clang %c_filenames% %c_flags% -o ../bin/%target%.dll %defines% %inc_flags% %lnk_flags%