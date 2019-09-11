#include <stdlib.h> 
#include <time.h>

#include "chip8.h"

Chip8::Chip8()
{
    clearMemAndRegisters();    
    initOpCodes();
}

void Chip8::loadRom(Rom rom)
{
    if(rom.romLength > memorySize - roomStartMemory)
    {
        std::cout << "Rom is to large!";
        return;
    }

    for(int i = 0; i < rom.romLength; i++)
    {
        memory[i + roomStartMemory] = rom.content[i];
    }
    std::cout << "Rom loaded ... \n";

    pc = 512;
    nextOpcode = memory[pc] << 8 | memory[pc+1];
}

void Chip8::processCycle()
{
    if(!opcodeError && (!paused || step))
    {
        currentOpcode = nextOpcode;        
        if(opcodeLookup.find(currentOpcode & 0xF000) != opcodeLookup.end())
        {
            auto opcodeFunc = opcodeLookup[currentOpcode & 0xF000];
            opcodeFunc(currentOpcode & 0x0FFF);

            step = false;
            pc += 2;
            nextOpcode = memory[pc] << 8 | memory[pc+1];
        }
        else 
        {
            opcodeError = true;
            nextOpcode = 0;
        }
    }    
}

void Chip8::clearMemAndRegisters()
{
    memset(memory, 0, memorySize);
    memset(registers, 0, 15);
    memcpy(memory, chip8Fontset, sizeof(chip8Fontset));
}

void Chip8::initOpCodes()
{
    srand((int) time(NULL));

    zeroOpcodeLookup[0x00E0] = [this] { memset(pixels, 0, 64 * 32); }; // CLS
    zeroOpcodeLookup[0x00EE] = [this] { pc = stack.top(); stack.pop(); }; // RET

    eighthOpcodeLookup[0x0000] = [this](int x, int y) { registers[x] = registers[y]; };
    eighthOpcodeLookup[0x0001] = [this](int x, int y) { registers[x] = registers[x] | registers[y]; };
    eighthOpcodeLookup[0x0002] = [this](int x, int y) { registers[x] = registers[x] & registers[y]; };
    eighthOpcodeLookup[0x0003] = [this](int x, int y) { registers[x] = registers[x] ^ registers[y]; };
    eighthOpcodeLookup[0x0004] = [this](int x, int y) 
    { 
        int result = registers[x] + registers[y]; 
        flagRegister = result > 0xFF ? 1 : 0;
        registers[x] = result & 0x00FF;
    };
    eighthOpcodeLookup[0x0005] = [this](int x, int y) 
    { 
        flagRegister = registers[x] > registers[y] ? 1 : 0;
        registers[x] = registers[x] - registers[y];
    };
    eighthOpcodeLookup[0x0006] = [this](int x, int y) 
    { 
        flagRegister = registers[x] & 0x0F ? 1 : 0;
        registers[x] = registers[x] / 2;
    };
    eighthOpcodeLookup[0x0007] = [this](int x, int y)
    { 
        flagRegister = registers[y] > registers[x] ? 1 : 0;
        registers[x] = registers[y] - registers[x];
    };
    eighthOpcodeLookup[0x000E] = [this](int x, int y) 
    {
        flagRegister = registers[x] & 0xF0 ? 1 : 0;
        registers[x] = registers[x] / 2;
    };

    sixteenOpcodeLookup[0x007] = [this](int x, int code) { };

    opcodeLookup[0x0000] = [this](int i) { zeroOpcodeLookup[i](); };
    opcodeLookup[0x1000] = [this](int i) { pc = i; }; // JP addr
    opcodeLookup[0x2000] = [this](int i) { stack.push(pc); pc = i; }; // CALL addr
    opcodeLookup[0x3000] = [this](int i) { if(registers[i & 0x0F00 >> 8] == (i & 0x00FF)) pc += 2; }; // SE Vx, byte
    opcodeLookup[0x4000] = [this](int i) { if(registers[i & 0x0F00 >> 8] != (i & 0x00FF)) pc += 2; }; // SNE Vx, byte
    opcodeLookup[0x5000] = [this](int i) { if(registers[i & 0x0F00 >> 8] == registers[i & 0x00F0]) pc += 2; }; // SE Vx, Vy
    opcodeLookup[0x6000] = [this](int i) { registers[i & 0x0F00 >> 8] = i & 0x00FF; }; // LD Vx, byte
    opcodeLookup[0x7000] = [this](int i) { registers[i & 0x0F00 >> 8] = registers[i & 0x0F00 >> 8] + (i & 0x00FF); }; // ADD Vx, byte
    opcodeLookup[0x8000] = [this](int i) { eighthOpcodeLookup[i & 0x000F](i & 0x0F00 >> 8, i & 0x00F0 >> 4); };
    opcodeLookup[0x9000] = [this](int i) { if(registers[i & 0x0F00 >> 8] != registers[i & 0x00F0 >> 4]) pc += 2; }; // SNE Vx, Vy
    opcodeLookup[0xA000] = [this](int i) { iRegister = i & 0x0FFF; }; // LD I, addr
    opcodeLookup[0xB000] = [this](int i) { pc = (i & 0x0FFF) + registers[0]; }; // JP V0, addr
    opcodeLookup[0xC000] = [this](int i) { int randomNumber = (rand() % 255) & (i & 0x00FF); registers[i & 0x0F00 >> 8] = randomNumber; }; // Cxkk - RND Vx, byte
    opcodeLookup[0xD000] = [this](int i) // DRW Vx, Vy, nibble
    { 
        int x = (i & 0x0F00) >> 8;
        int y = (i & 0x00F0) >> 4;
        int n = (i & 0x000F);
    };
    //TODO opcodeLookup[0xE000] = [this](int i) { }; 
    opcodeLookup[0xF000] = [this](int i) { sixteenOpcodeLookup[i & 0x00FF](i & 0x0F00 >> 8, i & 0x00FF); };
}