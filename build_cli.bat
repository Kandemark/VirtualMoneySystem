@echo off
echo Building VirtualMoneySystem CLI Client...

REM Find Visual Studio
for /f "usebackq tokens=*" %%i in (`"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath`) do set VS_PATH=%%i

if not defined VS_PATH (
    echo ERROR: Visual Studio not found
    exit /b 1
)

REM Setup environment
call "%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1

REM Compile CLI Client
echo Compiling CLI...
cl.exe /EHsc /std:c++20 /O2 /Fe:VirtualMoneyCLI.exe client\VirtualMoneyCLI.cpp

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [SUCCESS] CLI client built!
    echo Run: VirtualMoneyCLI.exe
    echo.
    echo Make sure VirtualMoneySystem.exe is running first!
) else (
    echo [ERROR] Build failed
    exit /b 1
)
