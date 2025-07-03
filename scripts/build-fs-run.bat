@echo off
cd /d %~dp0
call build.bat
cd /d %~dp0
call build-fs.bat
cd /d %~dp0\..
cd release\bin
call grachi.exe