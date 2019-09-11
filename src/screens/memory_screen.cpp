#include <string>
#include <iomanip>
#include <algorithm>

#include "memory_screen.h"
#include "../helper/string_helper.h"

MemoryScreen::MemoryScreen(int row, int column, Chip8* chip8) : Screen(row, column), chip8(chip8)
{     
    setClearColor({ 255, 255, 255, 255});
}

void MemoryScreen::draw()
{ 
    Color black = { 0, 0, 0, 255};
    Color orange = { 255, 165, 0, 255};

    drawText(5, 20, "MEMORY", black);
    drawText(5, 30, "------------", black);
    
    int memoryStart = chip8->pc > 5 ? chip8->pc - 5 : chip8->pc;
    int memoryEnd = chip8->pc + 17 < chip8->memorySize ? chip8->pc + 17 : chip8->memorySize;
    for(int i = memoryStart; i < memoryEnd; i++)
    {
        float yOffset = (float) 45 + (20 * (i - memoryStart));
        drawText(20, yOffset, std::to_string(i), i == chip8->pc ? orange : black);
        drawText(65, yOffset, StringHelper::IntToHexString(static_cast<int>(chip8->memory[i]), 2), black);
    }
}