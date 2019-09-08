#pragma once
#ifndef CHIP8_H
#define CHIP8_H

#include "rom.h"

class Chip8
{
    public:
        void loadRom(Rom rom);

        int memOffset = 512; // 512bytes at the beginning of the memory contained the original interpreter
        int memorySize = 4096;
        unsigned char memory[4096]; // 4KB Ram

        unsigned short pc; // programm counter
        unsigned short iRegister; // 1 16-Bit Register (short = 2 byte = 16 bit)
        unsigned char registers[16]; // 16 8-Bit Registers (1 char = 1 byte = 8 bit)

        unsigned char pixels[64 * 32]; // state of the display pixels

        unsigned char timerDelay;
        unsigned char timerSound; 
};

#endif