@echo off
cd /d "%~dp0"

set "EMSDK_PATH=.\emsdk"
set "SOURCE_DIR=.\TicTacToe\myCode"
set "SERVER_PORT=8000"

echo ============================================
echo      Tic-Tac-Toe Web Launcher (Debug)
echo ============================================

echo [Check] Looking for EMSDK at: %CD%\%EMSDK_PATH%
if not exist "%EMSDK_PATH%\emsdk_env.bat" (
    echo [ERROR] CRITICAL FAIL: Could not find emsdk_env.bat!
    echo Current Directory is: %CD%
    echo Expected to find: %EMSDK_PATH%\emsdk_env.bat
    pause
    exit /b 1
)

echo [Check] Looking for Source Code at: %CD%\%SOURCE_DIR%
if not exist "%SOURCE_DIR%" (
    echo [ERROR] CRITICAL FAIL: Could not find source directory!
    echo Current Directory is: %CD%
    echo Expected to find: %SOURCE_DIR%
    pause
    exit /b 1
)

echo [1/4] Activating Emscripten (This might take a second)...
call "%EMSDK_PATH%\emsdk_env.bat"

where emcc >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Environment activation failed. 'emcc' command not found.
    pause
    exit /b 1
)

echo [2/4] Entering source directory...
pushd "%SOURCE_DIR%"

echo [2b/4] Compiling C++ to WebAssembly...
call emcc -O3 --bind -o game.js ^
    WasmEntry.cpp CGame.cpp CBoard.cpp CPlayer.cpp CHuman.cpp CComputer.cpp CDisplay.cpp ^
    -s ALLOW_MEMORY_GROWTH=1 ^
    -s NO_EXIT_RUNTIME=1

if %errorlevel% neq 0 (
    echo [ERROR] Compilation Failed!
    popd
    pause
    exit /b 1
)

echo [3/4] Opening Browser...
start http://localhost:%SERVER_PORT%/index.html

echo [4/4] Starting Server...
echo Press CTRL+C to stop.
python -m http.server %SERVER_PORT%

popd
echo Script Finished.
pause