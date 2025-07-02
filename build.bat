@echo off
setlocal

REM This script configures and builds the project for Windows.
REM By default:
REM It builds the 'Release' configuration.
REM It builds into a 'build' subdirectory.
REM It builds tests and tools as well.
REM
REM You can:
REM Override build type with --config <build-type>.
REM Override build path with -B <path-to-build>
REM Turn off the build of tests and/or tools.
REM You can add other CMake configuration options
REM
REM Example Usage:
REM   .\build.bat
REM   .\build.bat --config Debug
REM   .\build.bat -B build_debug --config Debug -DGAMEOFLIFE_BUILD_TESTS=OFF

SET BUILD_TYPE=Release
SET BUILD_FOLDER=build
SET CMAKE_ARGS=

REM --- Parse Command-Line Arguments ---
:ArgLoop
IF "%1"=="" GOTO EndArgLoop

IF /I "%1"=="--config" (
    SET "BUILD_TYPE=%2"
    SHIFT /1
    SHIFT /1
    GOTO ArgLoop
)

IF /I "%1"=="-B" (
    SET "BUILD_FOLDER=%2"
    SHIFT /1
    SHIFT /1
    GOTO ArgLoop
)

REM Any other argument is stored to be passed directly to CMake configuration
SET CMAKE_ARGS=%CMAKE_ARGS% %1
SHIFT /1
GOTO ArgLoop
:EndArgLoop

ECHO --- Configuring project in '%BUILD_FOLDER%' (Build type: %BUILD_TYPE%) ---
cmake -S . -B %BUILD_FOLDER% %CMAKE_ARGS%
IF %ERRORLEVEL% NEQ 0 (
    ECHO "CMake configure failed."
    exit /B 1
)

ECHO --- Building project ---
cmake --build %BUILD_FOLDER% --config %BUILD_TYPE%
IF %ERRORLEVEL% NEQ 0 (
    ECHO "CMake build failed."
    exit /B 1
)

ECHO.
ECHO Build complete! Executables can be found in the '%BUILD_FOLDER%\bin' directory.

endlocal
exit /B 0 REM exit script without closing the terminal