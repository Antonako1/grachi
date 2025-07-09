# CMakeList.txt : CMake project for Grachi, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.16)
project(Grachi VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(Grachi 
    Grachi.cpp
 "Menu.cpp" "CommonNon.cpp" "Settings.cpp")

target_include_directories(Grachi PRIVATE ${CMAKE_SOURCE_DIR})


set(LIBS_DIR "${CMAKE_SOURCE_DIR}/libs")

# Add Arghand
target_include_directories(Grachi PRIVATE ${LIBS_DIR}/Arghand-1.2.0/Include)

# Add ATRC
set(ATRC_DIR "${LIBS_DIR}/ATRC_2.2.0/cmake")
find_package(ATRC REQUIRED)
target_link_libraries(Grachi PRIVATE ${ATRC_LIB_RELEASE})
target_include_directories(Grachi PRIVATE ${ATRC_INCLUDE_DIR})

if(WIN32)
    # For Windows, copy DLLs to the output directory
    add_custom_command(TARGET Grachi POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ATRC_DLL_RELEASE}" $<TARGET_FILE_DIR:Grachi>
    )
endif()

# Add raylib
set(raylib_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/share/raylib")
find_package(raylib CONFIG REQUIRED)
target_link_libraries(Grachi PRIVATE raylib)