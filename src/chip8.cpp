#include <stdlib.h> 
#include <ctime>

#include "chip8.h"
#include "helper/string_helper.h"

Chip8::Chip8()
{
    clearMemAndRegisters();    
    initOpCodes();
}

void Chip8::loadRom(Rom rom)
{
    if(rom.romLength > memorySize - romStartMemory)
    {
        std::cout << "Rom is to large!";
        return;
    }

    memcpy(&memory[romStartMemory], rom.content, rom.romLength);
    std::cout << "Rom loaded ... \n";

    pc = romStartMemory;
    nextOpcode = memory[pc] << 8 | memory[pc+1];
}

void Chip8::togglePause()
{
    paused = !paused;
    if(paused) clock.Reset();
}

void Chip8::processCycle()
{
    int delayCycles = step ? 1 : clock.CatchUpTimerCycles(frequency);
    if(timerDelay > 0) timerDelay = timerDelay - delayCycles < 0 ? 0 : timerDelay - delayCycles; 
    if(timerSound > 0) timerSound = timerSound - delayCycles < 0 ? 0 : timerSound - delayCycles;

    int cycles = step ? 1 : clock.CatchUpChipCycles(frequency);
    if(!opcodeError && (!paused || step) && cycles > 0)
    {
        try
        {
            for(int i = 0; i < cycles; i++)
            {
                currentOpcode = nextOpcode;       
                pc += 2; // Increment PC before executing Opcode function
                auto opcodeFunc = opcodeMap[currentOpcode & 0xF000];
                opcodeFunc(currentOpcode & 0x0FFF);

                nextOpcode = memory[pc] << 8 | memory[pc+1];
                step = false;

                if(drawSprite) break;
            }     
            drawSprite = false;     
        }
        catch(const std::bad_function_call& e)
        {
            std::cerr << e.what() << '\n';
            opcodeError = true;
            nextOpcode = 0;
        }
    }    
}

void Chip8::clearMemAndRegisters()
{
    memset(memory, 0, memorySize);
    memset(pixels, 0, 64 * 32);
    memset(registers, 0, 15);
    memset(keys, 0, 15);
    memcpy(memory, chip8Fontset, sizeof(chip8Fontset));
}

void Chip8::initOpCodes()
{
    srand((int) time(NULL));

    // Main Map
    opcodeMap[0x0000] = [this](int i) { opcodeMap0[i](); };
    opcodeMap[0x1000] = [this](int i) { pc = i; }; // JP addr
    opcodeMap[0x2000] = [this](int i) { stack.push(pc); pc = i; }; // CALL addr
    opcodeMap[0x3000] = [this](int i) { if(registers[(i & 0x0F00) >> 8] == (i & 0x00FF)) pc += 2; }; // SE Vx, byte
    opcodeMap[0x4000] = [this](int i) { if(registers[(i & 0x0F00) >> 8] != (i & 0x00FF)) pc += 2; }; // SNE Vx, byte
    opcodeMap[0x5000] = [this](int i) { if(registers[(i & 0x0F00) >> 8] == registers[(i & 0x00F0) >> 4]) pc += 2; }; // SE Vx, Vy
    opcodeMap[0x6000] = [this](int i) { registers[(i & 0x0F00) >> 8] = i & 0x00FF; }; // LD Vx, byte
    opcodeMap[0x7000] = [this](int i) { registers[(i & 0x0F00) >> 8] += i & 0x00FF; }; // ADD Vx, byte
    opcodeMap[0x8000] = [this](int i) { opcodeMap8[i & 0x000F]((i & 0x0F00) >> 8, (i & 0x00F0) >> 4); };
    opcodeMap[0x9000] = [this](int i) { if(registers[(i & 0x0F00) >> 8] != registers[(i & 0x00F0) >> 4]) pc += 2; }; // SNE Vx, Vy
    opcodeMap[0xA000] = [this](int i) { iRegister = i & 0x0FFF; }; // LD I, addr
    opcodeMap[0xB000] = [this](int i) { pc = (i & 0x0FFF) + registers[0]; }; // JP V0, addr
    opcodeMap[0xC000] = [this](int i) { int randomNumber = (rand() % 255) & (i & 0x00FF); registers[(i & 0x0F00) >> 8] = randomNumber; }; // Cxkk - RND Vx, byte
    opcodeMap[0xD000] = [this](int i) // DRW Vx, Vy, nibble
    { 
        short x = registers[(i & 0x0F00) >> 8];
        short y = registers[(i & 0x00F0) >> 4];
        short height = i & 0x000F;
        short sprite;

        flagRegister = 0;
        for(short yLine = 0; yLine < height; yLine++)
        {   
            sprite = memory[iRegister + yLine];
            for(short xLine = 0; xLine < 8; xLine++)
            {
                if(((sprite >> (7 - xLine)) & 1) == 1)
                {
                    if(pixels[(x + xLine) + ((y + yLine) * 64)] == 1)
                    {
                        flagRegister = 1;
                    }
                    pixels[(x + xLine) + ((y + yLine) * 64)] ^= 1;
                }
            }
        }
        drawSprite = true;
    };
    opcodeMap[0xE000] = [this](int i) { opcodeMapE[i & 0x00FF]((i & 0x0F00) >> 8); }; 
    opcodeMap[0xF000] = [this](int i) { opcodeMapF[i & 0x00FF]((i & 0x0F00) >> 8); };

    // Sub Maps
    opcodeMap0[0x00E0] = [this] { memset(pixels, 0, 64 * 32); }; // CLS
    opcodeMap0[0x00EE] = [this] { pc = stack.top(); stack.pop(); }; // RET

    opcodeMap8[0x0000] = [this](int x, int y) { registers[x] = registers[y]; };
    opcodeMap8[0x0001] = [this](int x, int y) { registers[x] = registers[x] | registers[y]; };
    opcodeMap8[0x0002] = [this](int x, int y) { registers[x] = registers[x] & registers[y];; };
    opcodeMap8[0x0003] = [this](int x, int y) { registers[x] = registers[x] ^ registers[y]; };
    opcodeMap8[0x0004] = [this](int x, int y) 
    { 
        int result = registers[x] + registers[y]; 
        flagRegister = result > 0xFF ? 1 : 0;
        registers[x] = result & 0x00FF;
    };
    opcodeMap8[0x0005] = [this](int x, int y) 
    { 
        flagRegister = registers[x] > registers[y] ? 1 : 0;
        registers[x] = registers[x] - registers[y];
    };
    opcodeMap8[0x0006] = [this](int x, int y) 
    { 
        flagRegister = registers[x] & 0x0F;
        registers[x] = (registers[x] & 0xF0) >> 1;
    };
    opcodeMap8[0x0007] = [this](int x, int y)
    { 
        flagRegister = registers[y] > registers[x] ? 1 : 0;
        registers[x] = registers[y] - registers[x];
    };
    opcodeMap8[0x000E] = [this](int x, int y) 
    {
        flagRegister = registers[x] & 0xF0;
        registers[x] = (registers[x] & 0x0F) << 1;
    };

    opcodeMapF[0x007] = [this](int x) { registers[x] = timerDelay; };
    //opcodeMapF[0x00A] = [this](int x) { register[x] = timerDelay; }; // KEY PRESS WAIT
    opcodeMapF[0x015] = [this](int x) { timerDelay = registers[x]; };
    opcodeMapF[0x018] = [this](int x) { timerSound = registers[x]; };
    opcodeMapF[0x01E] = [this](int x) { iRegister += registers[x]; };
    opcodeMapF[0x029] = [this](int x) { iRegister = registers[x] * 5; };
    opcodeMapF[0x033] = [this](int x) 
    { 
        memory[iRegister] = registers[(x & 0x0F00) >> 8] / 100;
        memory[iRegister + 1] = (registers[(x & 0x0F00) >> 8] / 10) % 10;
        memory[iRegister + 2] = registers[(x & 0x0F00) >> 8] % 10;
    };
    opcodeMapF[0x055] = [this](int x) 
    { 
        for(short i = 0; i <= x; i++)
        {
            memcpy(&memory[iRegister + i], &registers[i], 2);
        }
    };
    opcodeMapF[0x065] = [this](int x) 
    { 
        for(short i = 0; i <= x; i++)
        {
            memcpy(&registers[i], &memory[iRegister + i], 2);
        }
    };

    opcodeMapE[0x009E] = [this](int x) { if(keys[x] == 1) pc += 2; };
    opcodeMapE[0x00A1] = [this](int x) { if(keys[x] != 1) pc += 2; };
}