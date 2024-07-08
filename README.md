## Build and run

### Requirements:
    
- OpenCV [4.10.0](https://opencv.org/releases/)
    - Download Windows version and copy the contents of \build\ directory into .\opencv\
- ATRC's latest [release](https://github.com/Antonako1/ATRC/releases)

### Windows, Visual Studio:

- C++ CMake tools for windows
- C++ v14.xx build tools for (processor)
- MSVC build tools

#### NOTE: See .\win\scripts\globals.bat. Enter your paths there, or the executable programs if they are found in the path

#### Build project:

- .\win\build.bat

#### Run project:

- .\win\run.bat [args...]

#### Build and run the project:

- .\build_n_run.bat [args...]

#### Clear build:

- .\win\scripts\del.bat


#### Releasing:

    In .\release_building, run win.bat
