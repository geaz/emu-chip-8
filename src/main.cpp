#define STB_TRUETYPE_IMPLEMENTATION

#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "opengl/window.hpp"
#include "opengl/structs.hpp"

#include "rom.hpp"
#include "chip8.hpp"
#include "screens/chip8_screen.hpp"
#include "screens/memory_screen.hpp"
#include "screens/register_screen.hpp"

int main(int argc, char* argv[]) 
{
    if(argc < 2)
    {
        std::cout << "Please enter a rom path as argument!";
        return 0;
    }

    Rom rom(argv[1]);

    Chip8 chip8;
    chip8.loadRom(rom);

    Window window("CHIP-8", 864, 480);
    window.setClearColor(255, 255, 255, 255);
    window.addColumnDefinition({ 0, 82.5f });
    window.addColumnDefinition({ 1, 17.5f });
    window.addRowDefinition({ 0, 75.0f });
    window.addRowDefinition({ 1, 25.0f });
    
    Chip8Screen chip8Screen(0, 0, &chip8);  
    MemoryScreen memoryScreen(0, 1, &chip8);
    RegisterScreen registerScreen(1, 0, &chip8);

    window.addScreen(&chip8Screen);
    window.addScreen(&registerScreen);
    window.addScreen(&memoryScreen);

    window.startLoop();
    
    return 0;
}