cmake_minimum_required(VERSION 3.1.0)
project(emu-chip-8 VERSION 0.1.0)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-GLFW.txt)

set(EMU_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/structs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/font.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shader.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/screen.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screens/display.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/rom.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/chip8.h
)

set(EMU_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c

    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screens/display.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/rom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/chip8.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

include_directories(${GLFW_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include)

link_directories(${GLFW_LIBRARY_DIR})

add_executable(emu-chip-8 ${EMU_SOURCES} ${EMU_HEADERS})
add_dependencies(emu-chip-8 glfw)

target_link_libraries(emu-chip-8 glfw3 ${OPENGL_LIBRARIES})