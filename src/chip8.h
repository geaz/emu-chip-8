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

        int roomStartMemory = 512; // 512bytes at the beginning of the memory contained the original interpreter
        int memorySize = 4096;
        unsigned char memory[4096]; // 4KB Ram

        unsigned short pc; // programm counter
        unsigned short iRegister; // 1 16-Bit Register (short = 2 byte = 16 bit)
        unsigned char registers[15]; // 15 8-Bit Registers (1 char = 1 byte = 8 bit)
        unsigned char flagRegister; // + 1 8-Bit Regsiter - forbidden to be used by programs

        unsigned char pixels[64 * 32]; // state of the display pixels

        unsigned char timerDelay;
        unsigned char timerSound; 

        int currentOpcode;
        bool opcodeError = false;

    private:
        void initOpCodes();

        std::map<int, std::function<void(const int)>> opcodeLookup;
        std::map<int, std::function<void()>> zeroOpcodeLookup;        
        std::map<int, std::function<void(const int, const int)>> eighthOpcodeLookup;        
        std::map<int, std::function<void(const int, const int)>> sixteenOpcodeLookup;
};

#endif