@echo off
cd %~dp0..
setlocal enabledelayedexpansion

set "SOURCE=.\assets"
set "TARGET_ROOT=.\build"

rem If an output directory is passed (post-build), copy only there
if not "%~1"=="" (
    xcopy /e /i /y /q "%SOURCE%" "%~1\assets\"
    exit /b 0
)

rem Otherwise copy to every build output folder except deps
for /d %%D in ("%TARGET_ROOT%\*") do (
    if /I not "%%~nxD"=="deps" (
        for /d %%C in ("%%D\*") do (
            xcopy /e /i /y /q "%SOURCE%" "%%C\assets\"
        )
    )
)
