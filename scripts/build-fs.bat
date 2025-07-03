@echo off
cd /d %~dp0\..
mkdir release
mkdir release\html
mkdir release\bin
mkdir release\config
mkdir release\assets

copy html\*.* release\html\
copy build\*.exe release\bin\
copy build\*.dll release\bin\
copy config\*.* release\config\
xcopy /e/q/y assets\*.* release\assets\