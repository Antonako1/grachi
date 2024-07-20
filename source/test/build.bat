@echo OFF
pushd %CD%
cd /d %~dp0
call ..\..\z-win\scripts\msvs-dev-env.bat
cd /d %~dp0
rmdir /s/q build
mkdir build
cd build
"C:\Windows\system32\cmd.exe" /c "%SYSTEMROOT%\System32\chcp.com 65001 >NUL && "%CMAKEPATH%\CMake\bin\cmake.exe"  -G "Ninja"  -DCMAKE_C_COMPILER:STRING="%COMPILERPATH%" -DCMAKE_CXX_COMPILER:STRING="%COMPILERPATH%" -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_INSTALL_PREFIX:PATH="./install/x64-debug"   -DCMAKE_MAKE_PROGRAM="%NINJAPATH%\ninja.exe" -DATRCBUILDCVPATH:PATH="%ATRCBUILDPATH%" -DSFMLBUILDCVPATH:PATH="%SFMLBUILDPATH%" -DUSEDEBUG:STRING="1" ".."
cmake --build . --config Debug
popd