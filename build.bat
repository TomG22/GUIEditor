@echo off

REM Default option is to build
if "%1"=="" (
    call :build
    goto end
)

REM Check for recognized options
if /i "%1"=="configure" (
    call :configure
) else if /i "%1"=="build" (
    call :configure
    call :build
) else if /i "%1"=="rebuild" (
    call :clean
    call :configure
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

if not exist build (
    mkdir build
)

cmake -S . -B build

goto :eof


REM ----------------------------------------
REM CMake build step
REM ----------------------------------------
:build

cmake --build build

goto :eof


REM ----------------------------------------
REM Delete the build dir
REM ----------------------------------------
:clean
rmdir /s /q build
goto :eof


:end
