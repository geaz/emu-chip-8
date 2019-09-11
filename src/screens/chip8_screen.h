#pragma once
#ifndef CHIP8SCREEN_H
#define CHIP8SCREEN_H

#include "../opengl/screen.h"
#include "../chip8.h"

class Chip8Screen : public Screen
{   
    public:
        Chip8Screen(int row, int column, Chip8* chip8);

        void draw() override;

        Chip8* chip8;
};

#endif // CHIP8SCREEN_H