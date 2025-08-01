@echo off

REM Define relative paths
set ROOT_DIR=%~dp0..
set BUILD_DIR=%ROOT_DIR%\build
set TOOLCHAIN_FILE=%ROOT_DIR%\toolchain.cmake

REM Default option is to configure and then build
if NOT "%2"=="" (
    echo ~ Either provide no options for a default build or only provide one
    goto :eof
)

if "%1"=="" (
    call :configure
    call :build
    goto :eof
)

REM An option was provided
if /i "%1"=="configure" (
    call :configure
) else if /i "%1"=="build" (
    call :build
) else if /i "%1"=="clean" (
    call :clean
) else (
    echo ~ Unrecognized option
    call :build
)


goto :eof


REM FUNCTION DEFINITIONS


REM ----------------------------------------
REM CMake configuration step
REM ----------------------------------------
:configure

if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

cmake -S "%ROOT_DIR%" -B "%BUILD_DIR%" -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN_FILE%"

goto :eof


REM ----------------------------------------
REM CMake build step
REM ----------------------------------------
:build

cmake --build "%BUILD_DIR%"

goto :eof


REM ----------------------------------------
REM Delete the build dir
REM ----------------------------------------
:clean
rmdir /s /q "%BUILD_DIR%"
goto :eof
