@echo off
cd /d "%~dp0"
setlocal
cd ..
if not exist build (
    mkdir build
)

cd build
cmake ..
cmake --build .

endlocal