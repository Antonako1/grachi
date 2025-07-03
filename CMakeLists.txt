cmake_minimum_required(VERSION 3.10)
project(grachi VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(grachi 
    source/main.cpp
)

# ATRC library configuration
set(ATRC_DIR "${CMAKE_SOURCE_DIR}/libs/ATRC_2.2.0/cmake")
find_package(ATRC REQUIRED)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_link_libraries(grachi PRIVATE ${ATRC_LIB_DEBUG})
else()
    target_link_libraries(grachi PRIVATE ${ATRC_LIB_RELEASE})
endif()
target_include_directories(grachi PRIVATE "${CMAKE_SOURCE_DIR}/libs/ATRC_2.2.0/include")

# Arghand library configuration
target_include_directories(grachi PRIVATE "${CMAKE_SOURCE_DIR}/libs/Arghand-1.1.0/include")



target_include_directories(grachi PRIVATE "${CMAKE_SOURCE_DIR}/source")

# Copy ATRC DLLs to the build directory
if(WIN32)
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(ATRC_DLL "${ATRC_DLL_DEBUG}")
    else()
        set(ATRC_DLL "${ATRC_DLL_RELEASE}")
    endif()

    add_custom_command(TARGET grachi POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ATRC_DLL}" "${CMAKE_BINARY_DIR}/ATRC.dll"
        COMMENT "Copying ATRC DLL to build directory")
endif()
