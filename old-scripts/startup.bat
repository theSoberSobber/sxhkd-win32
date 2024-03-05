@echo off
set /p "username=Enter your username: "

REM Check if the username variable is not empty
if not "%username%"=="" (
    REM Copy files to the destination folder
    copy "VirtualDesktopAccessor.dll" "C:\Users\%username%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup"
    copy "sxhkd-win32.exe" "C:\Users\%username%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup"

    if %errorlevel% equ 0 (
        echo Files copied successfully to Startup folder for user %username%.
    ) else (
        echo Error: Unable to copy files to Startup folder.
    )
) else (
    echo Error: Username cannot be empty.
)

pause
