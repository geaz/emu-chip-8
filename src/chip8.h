#pragma once
#ifndef CHIP8_H
#define CHIP8_H

#include <map>
#include <functional>
#include <stack> 

#include "rom.h"

class Chip8
{
    public:
        Chip8();

        void loadRom(const Rom rom);
        void processCycle();

        std::stack<int> stack;

        int romStartMemory = 512; // 512bytes at the beginning of the memory contained the original interpreter
        int memorySize = 4096;
        unsigned char memory[4096]; // 4KB Ram

        unsigned short pc; // programm counter
        unsigned char registers[15]; // 15 8-Bit Registers (1 char = 1 byte = 8 bit)
        unsigned char flagRegister = 0; // + 1 8-Bit Regsiter - forbidden to be used by programs
        unsigned short iRegister = 0; // 1 16-Bit Register (short = 2 byte = 16 bit)

        unsigned char pixels[64 * 32]; // state of the display pixels

        unsigned char timerDelay = 0;
        unsigned char timerSound = 0; 

        int currentOpcode = 0, nextOpcode = 0;
        bool opcodeError = false;
        bool paused = true;
        bool step = false;

    private:
        void clearMemAndRegisters();
        void initOpCodes();

        std::map<int, std::function<void(const int)>> opcodeMap;
        std::map<int, std::function<void()>> opcodeMap0;        
        std::map<int, std::function<void(const int, const int)>> opcodeMap8;        
        std::map<int, std::function<void(const int)>> opcodeMapF;

        unsigned char chip8Fontset[80] =
        { 
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };
};

#endif