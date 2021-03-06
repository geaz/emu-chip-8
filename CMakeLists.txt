cmake_minimum_required(VERSION 3.1.0)
project(emu-chip-8 VERSION 0.1.0)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-GLFW.txt)

set(EMU_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/helper/string_helper.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/stb/stb_truetype.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/resource_manager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/structs.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/font.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shader.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/screen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screens/chip8_screen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screens/memory_screen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screens/register_screen.hpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clock.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rom.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/chip8.hpp
)

set(EMU_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c

    ${CMAKE_CURRENT_SOURCE_DIR}/src/helper/string_helper.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/resource_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/font.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screens/chip8_screen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screens/memory_screen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screens/register_screen.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/clock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/chip8.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

include_directories(${GLFW_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include)

link_directories(${GLFW_LIBRARY_DIR})

add_executable(emu-chip-8 ${EMU_SOURCES} ${EMU_HEADERS})
add_dependencies(emu-chip-8 glfw)

target_link_libraries(emu-chip-8 glfw3 ${OPENGL_LIBRARIES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fonts/Minecraft.ttf Minecraft.ttf COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/screen.vshader shaders/screen.vshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/screen.fshader shaders/screen.fshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/text.vshader shaders/text.vshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/text.fshader shaders/text.fshader COPYONLY)