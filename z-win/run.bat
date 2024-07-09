@echo off
cd /d %~dp0
call .\scripts\globals.bat
cd ..
cd ..\build
COPY /B ..\sfml\bin\*.dll .\win\
COPY /B ..\atrc\libs\win\*.dll .\win\
XCOPY /Y /E ..\assets\*.* .\win\assets\
.\win\%PROJECTNAME%.exe %*
echo %ERRORLEVEL%
cd ..