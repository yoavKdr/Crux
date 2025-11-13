@echo off

SETLOCAL ENABLEDELAYEDEXPANSION


rem ===== Declarations =====
:init
    rem -----Directorys-----
    set INC_DIR=inc

    set SRC_DIR=src
    set UTILS_DIR=%SRC_DIR%\utils

    set OUT_DIR=out
    set BIN_DIR=%OUT_DIR%\bin
    set OBJ_DIR=%OUT_DIR%\obj

    rem -----Files-----
    set MAIN_SRC=%SRC_DIR%\main.cpp
    set MAIN_OBJ=%OBJ_DIR%\main.o
    set MAIN_EXE=%BIN_DIR%\main.exe

    rem -----Tools-----
    set COMPILER=g++
    set GDB=gdb


rem ===== Declarations =====
:start
    clear

    echo Please select an option:
    echo 1) clean
    echo 2) build
    echo 3) run
    echo 4) cbr

    set /p input=

    if %input%==1 (goto clean) else if %input%==clean (goto clean) else if %input%==c (goto clean)
    if %input%==2 (goto build) else if %input%==build (goto build) else if %input%==b (goto build)
    if %input%==3 (goto run) else if %input%==run (goto run) else if %input%==r (goto run)
    if %input%==4 (goto cbr) else if %input%==cbr (goto cbr)

    echo Invalid input.
    goto end

:clean
    if exist %BIN_DIR% rmdir /s /q %BIN_DIR%
    if exist %OBJ_DIR% rmdir /s /q %OBJ_DIR%
    goto end

:build
    if not exist %OUT_DIR% mkdir %OUT_DIR%
    if not exist %BIN_DIR% mkdir %BIN_DIR%
    if not exist %OBJ_DIR% mkdir %OBJ_DIR%

    for /f "delims=" %%f in ('dir /b /a-d "%UTILS_DIR%\*.cpp"') do (
        %COMPILER% -I %INC_DIR% -c "%UTILS_DIR%\%%f" -o "%OBJ_DIR%\%%~nf.o"
    )

    SET OBJ_LIST=
    FOR %%f IN (%OBJ_DIR%\*.o) DO SET OBJ_LIST=!OBJ_LIST! %%f
    %COMPILER% -I %INC_DIR% %MAIN_SRC%  %OBJ_LIST% -o %MAIN_EXE%
    
    goto end

:run
    %MAIN_EXE%
    goto end

:cbr
    call :clean
    call :build
    call :run
    goto end

:end