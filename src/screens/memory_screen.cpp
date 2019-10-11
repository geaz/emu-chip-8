#include <string>
#include <iomanip>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "memory_screen.hpp"
#include "../helper/string_helper.hpp"

MemoryScreen::MemoryScreen(int row, int column, Chip8* chip8) : Screen(row, column), chip8(chip8)
{     
    setClearColor({ 255, 255, 255, 255});
}

void MemoryScreen::draw()
{ 
    Color offBlack = { 50, 50, 50, 255 };
    Color gray = { 160, 160, 160, 255 };
    Color orange = { 255, 165, 0, 255};

    drawText(5, 20, "MEMORY", offBlack);
    drawText(5, 30, "------------", offBlack);
    
    int memoryStart = chip8->pc > 5 ? chip8->pc - 5 : chip8->pc;
    int memoryEnd = chip8->pc + 17 < chip8->memorySize ? chip8->pc + 17 : chip8->memorySize;
    for(int i = memoryStart; i < memoryEnd; i++)
    {
        float yOffset = (float) 45 + (20 * (i - memoryStart));
        drawText(20, yOffset, std::to_string(i), i == chip8->pc ? orange : gray);
        drawText(65, yOffset, StringHelper::IntToHexString(static_cast<int>(chip8->memory[i]), 2), offBlack);
    }
}

void MemoryScreen::handleKeys(const int key, const int scancode, const int action, const int mods)
{
    if (key == GLFW_KEY_P && action == GLFW_RELEASE)
    {
        chip8->togglePause();
    }
    else if (key == GLFW_KEY_N && action == GLFW_RELEASE && chip8->paused)
    {
        chip8->step = true;
    }
}