#include <iostream>
#include <fstream>

#include "rom.h"
#include "chip8.h"

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

    for(int i = 0; i < rom.romLength; i++)
    {
        auto opcode = chip8.memory[i + 512] << 8 | chip8.memory[i + 513];
        std::cout << std::hex << opcode << "\n";
    }   

    return 0;
}