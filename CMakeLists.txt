cmake_minimum_required(VERSION 3.0.0)
project(emu-chip-8 VERSION 0.1.0)

include(CTest)
enable_testing()

set(EMU_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rom.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/chip8.h
)

set(EMU_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/chip8.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(emu-chip-8 ${EMU_SOURCES} ${EMU_HEADERS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
