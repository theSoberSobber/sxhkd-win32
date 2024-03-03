@echo off

REM Check if running with administrative privileges
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo This script requires administrative privileges. Please run this script as an administrator.
    pause
    exit /b 1
)

REM Prompt the user to enter the name of the executable
set /p exeName=Enter the name of the executable (without extension): 

REM Get the absolute path of the directory where this script is located
for %%i in ("%~dp0.") do set "scriptDir=%%~fi"

REM Create the full path to the executable
set "exePath=%scriptDir%\%exeName%.exe"

echo User Input Executable Path: %exePath%

REM Check if the executable exists
if not exist "%exePath%" (
    echo Error: The specified executable does not exist.
    pause
    exit /b 1
)

REM Create the registry entry for startup
set "registryKey=HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run"
set "registryValue=sxhkd-win32"
set "registryData=%scriptDir%\%exeName%.exe"

echo Adding Registry Key %registryKey%\%registryValue% with value as %registryData%
REM Add the registry entry
reg add "%registryKey%" /v "%registryValue%" /t REG_SZ /d "%registryData%" /f >nul

REM Check if the registry entry was added successfully
if %errorlevel% neq 0 (
    echo Error: Failed to add the registry entry.
    pause
    exit /b 1
)

echo Startup entry added successfully.
pause
exit /b