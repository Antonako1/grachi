@echo off
cd /d %~dp0\..

mkdir release
mkdir release\assets
mkdir release\config

xcopy /Y /E /Q assets\* release\assets\
xcopy /Y /E /Q config\* release\config\
xcopy /Y /E /Q src\* release\

REM Zip only the CONTENTS of the release folder, NOT the folder itself
cd release
"C:\Program Files\7-Zip\7z.exe" a -tzip ..\grachi.zip .\*
cd /d %~dp0\..
rem COPY /B "C:\Program Files\LOVE\love.exe+grachi.love" grachi.exe
