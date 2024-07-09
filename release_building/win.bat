@echo off
setlocal
set "_VERSION_=0.1.0"
set "ARCH=x86_64"
cd /d %~dp0
call ..\z-win\scripts\globals.bat
cd /d %~dp0


RMDIR /S /Q .\output
set "BUILD_DIR=.\output\win"
mkdir %BUILD_DIR%
call ..\z-win\batch\del.bat
call ..\z-win\build.bat "Release"
cd /d %~dp0
COPY /Y/B ..\build\win\%PROJECTNAME%.exe %BUILD_DIR%
REM INSTALLER BUILDING
if not exist %BUILD_DIR%\nsis mkdir %BUILD_DIR%\nsis
COPY .\installer.nsi %BUILD_DIR%\nsis
COPY ..\LICENSE.txt %BUILD_DIR%\nsis
MOVE %BUILD_DIR%\%PROJECTNAME%.exe %BUILD_DIR%\nsis
cd %BUILD_DIR%\nsis
makensis installer.nsi
DEL %PROJECTNAME%.exe
cd ..
MOVE .\nsis\*.exe .
REN *.exe %PROJECTNAME%-ver_%_VERSION_%-win-%ARCH%-installer.exe
DEL %PROJECTNAME%.exe
MOVE * ..
endlocal