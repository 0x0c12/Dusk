REM Build file for Engine(Dynamic Link Library - DLL)
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Snippet to fetch all .c files
SET c_filenames=
FOR /R %%f in (*.c) do (
    SET c_filenames=!c_filenames! %%f
)

REM Flags and arguments
SET target=Sandbox
SET c_flags=-g
SET inc_flags=-Isrc -I../Engine/src
SET lnk_flags=-L../bin/ -lEngine.lib
SET defines=-D_DEBUG -DDSK_IMPORT

REM Actual build process
ECHO "Building %target%%..."
clang %c_filenames% %c_flags% -o ../bin/%target%.exe %defines% %inc_flags% %lnk_flags%