@echo off 
cd /d %~dp0
cd z-win
call build.bat
if %ERRORLEVEL% NEQ 0 EXIT /B 1
call run.bat %*