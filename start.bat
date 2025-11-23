@echo off
echo Starting VirtualMoneySystem...
echo.

REM Check if executable exists
if not exist VirtualMoneySystem.exe (
    echo ERROR: VirtualMoneySystem.exe not found
    echo Please build the system first
    pause
    exit /b 1
)

REM Run the system
VirtualMoneySystem.exe
