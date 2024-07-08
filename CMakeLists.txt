if(NOT WIN32) #remove?
  message(FATAL_ERROR "Supported only for Windows")
endif()

cmake_minimum_required(VERSION 3.8)
set(DEBUGGING__ 1)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


set(project_name "grachi")


project(${project_name} LANGUAGES C CXX)

file(GLOB SOURCES 
"./source/*.c"
"./source/*.h"
"./source/*.cpp"
"./source/*.hpp"
)

# Look for ATRC
if (WIN32)
    set(ATRC_DIR "${ATRCBUILDCVPATH}/libs/win")
endif()
find_library(ATRC NAMES ATRC REQUIRED PATHS ${ATRC_DIR})
message(STATUS "ATRC library found at: ${ATRC}")
include_directories("${ATRCBUILDCVPATH}/include")

# Look for SFML
message(STATUS "Path to SFML: ${SFMLBUILDCVPATH}")
if (WIN32)
  set(SFML_BIN_PATH "${SFMLBUILDCVPATH}/bin")
  set(SFML_LIB_PATH "${SFMLBUILDCVPATH}/lib")
endif()

# Find the SFML libraries
set(SFML_COMPONENTS system window graphics network audio)
foreach(component ${SFML_COMPONENTS})
  find_library(SFML_${component}_LIBRARY NAMES sfml-${component}-d sfml-${component} PATHS ${SFML_LIB_PATH} NO_DEFAULT_PATH)
  if(SFML_${component}_LIBRARY)
    message(STATUS "Found SFML ${component} library: ${SFML_${component}_LIBRARY}")
    list(APPEND SFML_LIBRARIES ${SFML_${component}_LIBRARY})
  else()
    message(FATAL_ERROR "Could not find SFML ${component} library.")
  endif()
endforeach()

# Include SFML directories
include_directories("${SFMLBUILDCVPATH}/include")
include_directories("${SFMLBUILDCVPATH}/include/SFML")
message(STATUS "SFML header files at: ${SFMLBUILDCVPATH}/include/SFML")


# Look for OpenCV
message(STATUS "Path to OpenCV: ${OPENBUILDCVPATH}")
if (WIN32)
  set(OPENCV_DLL_PATH "${OPENBUILDCVPATH}/x64/vc16/bin")
  set(OPENCV_LIB_PATH "${OPENBUILDCVPATH}/x64/vc16/lib")
endif()
# Find the monolithic OpenCV library
find_library(OPENCV_WORLD_LIBRARY NAMES opencv_world4100d PATHS ${OPENCV_LIB_PATH} NO_DEFAULT_PATH)
if(OPENCV_WORLD_LIBRARY)
  message(STATUS "Found OpenCV world library: ${OPENCV_WORLD_LIBRARY}")
  set(OPENCV_LIBRARIES ${OPENCV_WORLD_LIBRARY})
else()
  message(FATAL_ERROR "Could not find OpenCV world library.")
endif()
link_libraries(${OPENCV_LIBRARIES})
# Include OpenCV directories
include_directories("${OPENBUILDCVPATH}/include")
include_directories("${OPENBUILDCVPATH}/include/opencv2")
message(STATUS "OpenCV header files at: ${OPENBUILDCVPATH}/include/opencv2")

# Add executable
add_executable(${project_name} ${SOURCES})

# On errors, abort build
# Compiler-specific options
if (DEBUGGING__)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${project_name} PRIVATE /WX /ZI)
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${project_name} PRIVATE -Werror -g)
  endif()
  add_compile_definitions(DEBUG)
  message("STATUS" "Added DEBUG flag")
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
message("STATUS" "CXX: ${CMAKE_CXX_FLAGS}")

