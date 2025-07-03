@echo off
cd /d "%~dp0"
setlocal
cd ..
cd build
call grachi.exe %*
endlocal