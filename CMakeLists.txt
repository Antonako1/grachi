cmake_minimum_required(VERSION 3.8)

# Ensure the project is supported on Windows
if(NOT WIN32)
  message(FATAL_ERROR "Supported only for Windows")
endif()

message(STATUS "For C++")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler target: ${CMAKE_CXX_COMPILER_TARGET}")
message(STATUS "Compiler toolchain: ${CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN}")
message(STATUS "Compiler id: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler loaded: ${CMAKE_CXX_COMPILER_LOADED}")
message(STATUS "Compiler predefined commands: ${CMAKE_CXX_COMPILER_PREDEFINES_COMMAND}")
message(STATUS "Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

message(STATUS "For C")
message(STATUS "Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Compiler target: ${CMAKE_C_COMPILER_TARGET}")
message(STATUS "Compiler toolchain: ${CMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN}")
message(STATUS "Compiler id: ${CMAKE_C_COMPILER_ID}")
message(STATUS "Compiler loaded: ${CMAKE_C_COMPILER_LOADED}")
message(STATUS "Compiler predefined commands: ${CMAKE_C_COMPILER_PREDEFINES_COMMAND}")
message(STATUS "Compiler version: ${CMAKE_C_COMPILER_VERSION}")

# set(CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE "x64")

set(DEBUG 1)
message(STATUS "Debug status: ${DEBUG}")

# Define the project name and languages
set(project_name grachi)
project(${project_name} LANGUAGES C CXX)

# Enable Hot Reload for MSVC compilers if supported
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Set the paths to your source files
file(GLOB SOURCES 
"source/*.c"
"source/*.h"
"source/*.cpp"
"source/*.hpp"
)

# Look for ATRC library
if (WIN32)
  set(ATRC_DIR "${ATRCBUILDCVPATH}/libs/win")
endif()
find_library(ATRC NAMES ATRC REQUIRED PATHS ${ATRC_DIR})
message(STATUS "ATRC library found at: ${ATRC}")
include_directories("${ATRCBUILDCVPATH}/include")

# Look for SFML libraries
set(SFML_DIR "${SFMLBUILDCVPATH}")
set(SFML_LIB_DIR "${SFML_DIR}/lib")
set(SFML_INCLUDE_DIR "${SFML_DIR}/include")
list(APPEND CMAKE_PREFIX_PATH "${SFML_DIR}")

find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)

if(NOT SFML_FOUND)
  MESSAGE(FATAL_ERROR "SFML not found")
endif()
# find_library(sfml-system sfml-window sfml-graphics sfml-audio)

# Add the executable target
add_executable(${project_name} ${SOURCES})


# Compiler-specific options
if (DEBUG)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${project_name} PRIVATE /WX /Zi)
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${project_name} PRIVATE -Werror -g)
  endif()
  add_compile_definitions(DEBUG)
else()
  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${project_name} PRIVATE /WX)
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${project_name} PRIVATE -Werror)
  endif()
endif()

# Set output directory based on OS
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/win")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/linux")
endif()

# Set RPATH for Unix-like systems
if (UNIX)
  set(CMAKE_BUILD_RPATH "${ATRC_DIR}")
  set(CMAKE_INSTALL_RPATH "${ATRC_DIR}")
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

# Link SFML libraries
target_include_directories(${project_name} PRIVATE ${SFML_INCLUDE_DIR})
# if(DEBUG)
#   target_link_libraries(
#     ${project_name} 
#     PRIVATE 
#     ${ATRC} 
#     "${SFML_LIB_DIR}/sfml-system-d.lib" 
#     "${SFML_LIB_DIR}/sfml-window-d.lib" 
#     "${SFML_LIB_DIR}/sfml-graphics-d.lib" 
#     "${SFML_LIB_DIR}/sfml-audio-d.lib"
#   )
# else()
  # target_link_libraries(
  #   ${project_name} 
  #   PRIVATE 
  #   ${ATRC} 
  #   sfml-system
  #   sfml-window
  #   sfml-graphics
  #   sfml-audio
  #   )
# endif()

target_link_libraries(${project_name} sfml-system sfml-window sfml-graphics sfml-audio)
message("STATUS" "CXX: ${CMAKE_CXX_FLAGS}")