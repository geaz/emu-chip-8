#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "opengl/window.h"
#include "opengl/structs.h"

#include "rom.h"
#include "chip8.h"
#include "screens/display.h"

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

    Window window("CHIP-8", 960, 480);
    window.setClearColor(255, 255, 255, 255);
    window.addColumnDefinition({ 0, 75.0f });
    window.addColumnDefinition({ 1, 25.0f });
    window.addRowDefinition({ 0, 75.0f });
    window.addRowDefinition({ 1, 25.0f });
    

    Display emuDisplay(0, 0);    

    Display emuDisplay2(0, 1);
    emuDisplay2.setClearColor({ 255, 255, 255, 255});

    Display emuDisplay3(1, 0);
    emuDisplay3.setClearColor({ 255, 255, 255, 255});

    window.addScreen(&emuDisplay);
    window.addScreen(&emuDisplay2);
    window.addScreen(&emuDisplay3);

    window.startLoop();
    
    return 0;
}