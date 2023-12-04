@echo off
>nul 2>&1 net file || goto :notAdmin

REM Continue with the script since it's running as admin
REM Get the current value of the registry key
for /f "tokens=3" %%a in ('reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v "NoWinKeys" 2^>nul ^| findstr /i "NoWinKeys"') do (
    set "currentValue=%%a"
)

REM Toggle the value of NoWinKeys
if "%currentValue%"=="0x1" (
    reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v "NoWinKeys" /t REG_DWORD /d 0 /f >nul
    echo The value of NoWinKeys is now 0
) else (
    reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v "NoWinKeys" /t REG_DWORD /d 1 /f >nul
    echo The value of NoWinKeys is now 1
)

echo Please restart your computer for changes to take place

pause
exit /b

:notAdmin
echo This script requires administrative privileges.
echo Please run the script as an administrator.
pause
