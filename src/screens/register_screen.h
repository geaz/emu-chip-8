#pragma once
#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include "../opengl/screen.h"
#include "../chip8.h"

class RegisterScreen : public Screen
{   
    public:
        RegisterScreen(int row, int column, Chip8* chip8);

        void draw();

        Chip8* chip8;
};

#endif // REGISTERSCREEN_H