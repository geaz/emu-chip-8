#pragma once
#ifndef MEMORYSCREEN_H
#define MEMORYSCREEN_H

#include "../opengl/screen.hpp"
#include "../chip8.hpp"

class MemoryScreen : public Screen
{   
    public:
        MemoryScreen(int row, int column, Chip8* chip8);

        void draw() override;
        void handleKeys(const int key, const int scancode, const int action, const int mods) override;

        Chip8* chip8;
};

#endif // MEMORYSCREEN_H