#include "chip8.h"

void Chip8::loadRom(Rom rom)
{
    if(rom.romLength > memorySize - memOffset)
    {
        std::cout << "Rom is to large!";
        return;
    }

    for(int i = 0; i < rom.romLength; i++)
    {
        memory[i + memOffset] = rom.content[i];
    }
    std::cout << "Rom loaded ... \n";
}