set ROOT_DIR=%~dp0..
set BUILD_DIR=%ROOT_DIR%\build
set TOOLCHAIN_FILE=%ROOT_DIR%\toolchain.cmake


if NOT "%2"=="" (
    echo ~ Build ERROR: Provide either no arguments for a default build or one of: configure ^| build ^| clean
    goto :eof
)

if "%1"=="" (
    call :configure
    call :build
    goto :eof
)

if /i "%1"=="configure" (
    call :configure
) else if /i "%1"=="build" (
    call :build
) else if /i "%1"=="clean" (
    call :clean
) else if /i "%1"=="run" (
    call :run
) else (
    echo ~ Build ERROR: Unrecognized argument: "%1"
    echo   Valid options: configure ^| build ^| clean
)

goto :eof


:configure
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)
cmake -S "%ROOT_DIR%" -B "%BUILD_DIR%" -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN_FILE%"
goto :eof


:build
cmake --build "%BUILD_DIR%"
goto :eof


:clean
rmdir /s /q "%BUILD_DIR%"
goto :eof
