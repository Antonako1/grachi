@echo off
cd /d %~dp0
call package.bat
cd /d %~dp0\..\release
set "LOVE=C:\Program Files\LOVE\love.exe"
cd /d %~dp0\..
call "%LOVE%" grachi.zip