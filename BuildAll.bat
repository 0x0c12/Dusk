@ECHO OFF
REM Building Everything

ECHO "Building Everything..."

mkdir bin

PUSHD Engine
CALL Build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

PUSHD Sandbox
CALL Build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

ECHO "All targets built!"