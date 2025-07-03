@echo off
cd /d "%~dp0"
setlocal
call build.bat
cd /d "%~dp0"
call run.bat %*
@REM endlocal