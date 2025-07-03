cmake_minimum_required(VERSION 3.10)
project(grachi VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/lib/cmake/SFML")
set(SFML_BIN_DIR "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin")
set(ATRC_DIR "${CMAKE_SOURCE_DIR}/libs/ATRC_2.2.0/cmake")
find_package(SFML 3.0.0 COMPONENTS System Window Graphics Audio REQUIRED)
find_package(ATRC REQUIRED)

# Add executable
add_executable(grachi 
    source/main.cpp
    source/main_menu.cpp
    source/game.cpp
    source/settings.cpp
    source/resources.cpp
)


target_link_libraries(grachi PRIVATE SFML::Graphics SFML::Audio SFML::System SFML::Window)
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
target_link_libraries(grachi PRIVATE ${CMAKE_SOURCE_DIR}/libs/TGUI-1.10/lib/tgui-d.lib)
target_link_libraries(grachi PRIVATE ${ATRC_LIB_DEBUG})
else()
target_link_libraries(grachi PRIVATE ${CMAKE_SOURCE_DIR}/libs/TGUI-1.10/lib/tgui.lib)
target_link_libraries(grachi PRIVATE ${ATRC_LIB_RELEASE})
endif()

target_include_directories(grachi PRIVATE "${CMAKE_SOURCE_DIR}/libs/TGUI-1.10/include")
target_include_directories(grachi PRIVATE "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/include")
target_include_directories(grachi PRIVATE "${CMAKE_SOURCE_DIR}/libs/Arghand-1.1.0/include")
target_include_directories(grachi PRIVATE "${CMAKE_SOURCE_DIR}/libs/ATRC_2.2.0/include")
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

# Copy TGUI DLLs to the build directory
if(WIN32)
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_custom_command(TARGET grachi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/libs/TGUI-1.10/bin/tgui-d.dll" "${CMAKE_BINARY_DIR}/tgui-d.dll"
            COMMENT "Copying TGUI Debug DLL to build directory")
    else()
        add_custom_command(TARGET grachi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/libs/TGUI-1.10/bin/tgui.dll" "${CMAKE_BINARY_DIR}/tgui.dll"
            COMMENT "Copying TGUI DLL to build directory")
    endif()
endif()

# Copy SFML DLLs to the build directory
if(WIN32)

    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_custom_command(TARGET grachi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_BIN_DIR}/sfml-graphics-d-3.dll" "${CMAKE_BINARY_DIR}/sfml-graphics-d-3.dll"
            COMMENT "Copying SFML Debug DLLs to build directory")
        add_custom_command(TARGET grachi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_BIN_DIR}/sfml-window-d-3.dll" "${CMAKE_BINARY_DIR}/sfml-window-d-3.dll"
            COMMENT "Copying SFML Debug DLLs to build directory")
        add_custom_command(TARGET grachi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_BIN_DIR}/sfml-system-d-3.dll" "${CMAKE_BINARY_DIR}/sfml-system-d-3.dll"
            COMMENT "Copying SFML Debug DLLs to build directory")
        add_custom_command(TARGET grachi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_BIN_DIR}/sfml-audio-d-3.dll" "${CMAKE_BINARY_DIR}/sfml-audio-d-3.dll"
            COMMENT "Copying SFML Debug DLLs to build directory")
    else()
        add_custom_command(TARGET grachi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_BIN_DIR}/sfml-graphics-3.dll" "${CMAKE_BINARY_DIR}/sfml-graphics-3.dll"
            COMMENT "Copying SFML DLLs to build directory")
        add_custom_command(TARGET grachi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_BIN_DIR}/sfml-window-3.dll" "${CMAKE_BINARY_DIR}/sfml-window-3.dll"
            COMMENT "Copying SFML DLLs to build directory")
        add_custom_command(TARGET grachi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_BIN_DIR}/sfml-system-3.dll" "${CMAKE_BINARY_DIR}/sfml-system-3.dll"
            COMMENT "Copying SFML DLLs to build directory")
        add_custom_command(TARGET grachi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_BIN_DIR}/sfml-audio-3.dll" "${CMAKE_BINARY_DIR}/sfml-audio-3.dll"
            COMMENT "Copying SFML DLLs to build directory")
    endif()
endif()
