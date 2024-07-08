@echo off
setlocal
set "_VERSION_=0.1.0"
set "ARCH=x86_64"
cd /d %~dp0
call ..\win\scripts\globals.bat
cd /d %~dp0

REM INSTALLER BUILDING
if not exist %BUILD_DIR%\nsis mkdir %BUILD_DIR%\nsis
COPY .\installer.nsi %BUILD_DIR%\nsis
COPY ..\LICENSE %BUILD_DIR%\nsis
COPY ..\README.txt %BUILD_DIR%\nsis
COPY .\setup.ps1 %BUILD_DIR%\nsis
COPY .\uninstall.ps1 %BUILD_DIR%\nsis
MOVE %BUILD_DIR%\%PROJECTNAME%.exe %BUILD_DIR%\nsis
cd %BUILD_DIR%\nsis
makensis installer.nsi
cd ..
MOVE .\nsis\*.exe .
REN *.exe %PROJECTNAME%-ver_%_VERSION_%-win-%ARCH%-installer.exe
DEL %PROJECTNAME%.exe
MOVE * ..
endlocal