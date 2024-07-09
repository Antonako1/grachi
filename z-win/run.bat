@echo off
cd /d %~dp0
call .\scripts\globals.bat
cd ..
cd ..\build
COPY /B ..\sfml\bin\*.dll .\win\ 
.\win\%PROJECTNAME%.exe %*
echo %ERRORLEVEL%
cd ..