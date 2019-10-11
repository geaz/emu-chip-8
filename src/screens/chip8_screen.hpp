#pragma once
#ifndef CHIP8SCREEN_H
#define CHIP8SCREEN_H

#include <map>

#include "../opengl/screen.hpp"
#include "../chip8.hpp"

class Chip8Screen : public Screen
{   
    public:
        Chip8Screen(int row, int column, Chip8* chip8);

        void draw() override;
        void drawPixelAt(const int x, const int y);
        void handleKeys(const int key, const int scancode, const int action, const int mods) override;

        Chip8* chip8;
        Shader pixelShader;

    private:
        std::map<int, char> keyMap = {
            { GLFW_KEY_1, 0x1 }, { GLFW_KEY_2, 0x2 }, { GLFW_KEY_3, 0x3 }, { GLFW_KEY_4, 0xC },
            { GLFW_KEY_Q, 0x4 }, { GLFW_KEY_W, 0x5 }, { GLFW_KEY_E, 0x6 }, { GLFW_KEY_R, 0xD },
            { GLFW_KEY_A, 0x7 }, { GLFW_KEY_S, 0x8 }, { GLFW_KEY_D, 0x9 }, { GLFW_KEY_F, 0xE },
            { GLFW_KEY_Y, 0xA }, { GLFW_KEY_X, 0x0 }, { GLFW_KEY_C, 0xB }, { GLFW_KEY_V, 0xF }
        };
};

#endif // CHIP8SCREEN_H