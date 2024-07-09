## Build and run

### Requirements and dependencies:

#### NOTE: See .\z-win\scripts\globals.bat. Enter your paths there, or the executable programs if they are found in the path
    
- ATRC's latest [release](https://github.com/Antonako1/ATRC/releases), used for data processing
    - Move the folder into the project's root and rename it into ```atrc```
- SFML [2.6.1](https://www.sfml-dev.org/download/sfml/2.6.1/) windows-vc17-32-bit, used for the user interface
    - Move the folder into project's root and rename it into ```sfml```

### Windows, Visual Studio:
- C++ CMake tools for windows
- C++ v14.xx build tools for (processor)
- MSVC build tools


#### Build project:
- .\z-win\build.bat

#### Run project:
- .\z-win\run.bat [args...]

#### Build and run the project:
- .\build_n_run.bat [args...]

#### Clear build:
- .\z-win\scripts\del.bat


#### Releasing:

    In .\release_building, run win.bat. It will create an installer executable.
