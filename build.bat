@echo off
setlocal enabledelayedexpansion

for /f "tokens=2 delims=:." %%i in ('chcp') do (
    set "CP=%%i"
    set "CP=!CP: =!"
)

if not "!CP!"=="65001" (
    chcp 65001 >nul
    "%~f0" --utf8-relaunched "!CP!" %*
    exit /b
)

if "%~1"=="--utf8-relaunched" (
    set "ORIGINAL_CP=%~2"
    shift
    shift
) else (
    set "ORIGINAL_CP=!CP!"
)

set "MAKE=.\make\make.exe"

set "LANGMODE=EN"
if "!ORIGINAL_CP!"=="866" set "LANGMODE=RU"
if "!ORIGINAL_CP!"=="1251" set "LANGMODE=RU"
if "!ORIGINAL_CP!"=="65001" set "LANGMODE=RU"

if "%LANGMODE%"=="RU" (
    set "MSG_THREADS=Обнаружено потоков CPU:"
    set "MSG_RECOMMENDED=Рекомендуемое количество:"
    set "MSG_ENTER=Введите количество потоков (Enter ="
    set "MSG_MENU1=1 - Сборка"
    set "MSG_MENU2=2 - Сборка и запуск"
    set "MSG_MENU3=3 - Очистка"
    set "MSG_CHOICE=Выберите действие: "
    set "MSG_DONE=Сборка завершена за"
) else (
    set "MSG_THREADS=Detected CPU threads: "
    set "MSG_RECOMMENDED=Recommended threads: "
    set "MSG_ENTER=Enter number of threads (Enter ="
    set "MSG_MENU1=1 - Build"
    set "MSG_MENU2=2 - Build and run"
    set "MSG_MENU3=3 - Clean"
    set "MSG_CHOICE=Select action: "
    set "MSG_DONE=Build finished in"
)

echo.
echo %MSG_THREADS% %NUMBER_OF_PROCESSORS%

set /a DEFAULT_THREADS=%NUMBER_OF_PROCESSORS%-1
if %DEFAULT_THREADS% LSS 1 set DEFAULT_THREADS=1

echo %MSG_RECOMMENDED% %DEFAULT_THREADS%
echo.

set /p "THREADS=%MSG_ENTER% %DEFAULT_THREADS%): "
if "%THREADS%"=="" set "THREADS=%DEFAULT_THREADS%"

echo.
echo %MSG_MENU1%
echo %MSG_MENU2%
echo %MSG_MENU3%
echo.

set /p "ACTION=%MSG_CHOICE%"

echo.

set "START=%TIME%"

if "%ACTION%"=="1" "%MAKE%" -j%THREADS%
if "%ACTION%"=="2" "%MAKE%" -j%THREADS% run
if "%ACTION%"=="3" "%MAKE%" clean

set "END=%TIME%"

echo.
echo %MSG_DONE% %START% ^> %END%

pause