@echo off
set /p "username=Enter your username: "

REM Check if the username variable is not empty
if not "%username%"=="" (
    REM Remove files from the destination folder
    del "C:\Users\%username%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\VirtualDesktopAccessor.dll" /f /q
    del "C:\Users\%username%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\sxhkd-win32.exe" /f /q

    if %errorlevel% equ 0 (
        echo Files removed successfully from the Startup folder for user %username%.
    ) else (
        echo Error: Unable to remove files from the Startup folder.
    )
) else (
    echo Error: Username cannot be empty.
)

pause
