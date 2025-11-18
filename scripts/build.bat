@echo off
REM ====================================================
REM   CMake Build Script for Windows
REM   Usage:
REM     build.bat              -> configure + build
REM     build.bat configure    -> only configure
REM     build.bat build        -> only build
REM     build.bat clean        -> remove build directory
REM ====================================================


REM -----------------------------
REM   Define relative paths
REM -----------------------------
set ROOT_DIR=%~dp0..
set BUILD_DIR=%ROOT_DIR%\build
set TOOLCHAIN_FILE=%ROOT_DIR%\toolchain.cmake


REM -----------------------------
REM   Handle arguments
REM -----------------------------
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


REM ====================================================
REM   CMake configuration step
REM   - Creates the build directory if it doesn't exist
REM   - Runs CMake to configure the project
REM ====================================================
:configure
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)
cmake -S "%ROOT_DIR%" -B "%BUILD_DIR%" -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN_FILE%"
goto :eof


REM ====================================================
REM   CMake build step
REM   - Builds the project from the configured files
REM ====================================================
:build
cmake --build "%BUILD_DIR%"
goto :eof


REM ====================================================
REM   Clean step
REM   - Deletes the entire build directory and contents
REM ====================================================
:clean
rmdir /s /q "%BUILD_DIR%"
goto :eof
