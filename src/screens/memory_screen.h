#pragma once
#ifndef MEMORYSCREEN_H
#define MEMORYSCREEN_H

#include "../opengl/screen.h"
#include "../chip8.h"

class MemoryScreen : public Screen
{   
    public:
        MemoryScreen(int row, int column, Chip8* chip8);

        void draw();

        Chip8* chip8;
};

#endif // MEMORYSCREEN_H