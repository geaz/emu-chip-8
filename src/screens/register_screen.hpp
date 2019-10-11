#pragma once
#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include "../opengl/screen.hpp"
#include "../chip8.hpp"

class RegisterScreen : public Screen
{   
    public:
        RegisterScreen(int row, int column, Chip8* chip8);

        void draw() override;

        Chip8* chip8;
};

#endif // REGISTERSCREEN_H