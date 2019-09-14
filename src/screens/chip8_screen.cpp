#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "chip8_screen.h"

Chip8Screen::Chip8Screen(int row, int column, Chip8* chip8) : Screen(row, column), chip8(chip8),
    pixelShader("shaders\\screen.vshader", "shaders\\screen.fshader")
{ 
    pixelShader.use();
    pixelShader.setVec4("clearColor", 0, 0, 255, 255);
}

void Chip8Screen::draw()
{ 
    chip8->processCycle();
    for(int i = 0; i < 64*32; i++)
    {
        if(chip8->pixels[i] == 1)
        {
            drawPixelAt(i%64, i/64);
        }
    }
}

/**
 *  Sets a rectangle on the screeen. It takes the native CHIP-8
 *  x and y coordinates and sets the pixel of the current screen
 *  by taking screen scales into consideration.
 * 
 *  @param  x   The x coordinate of the pixel on the CHIP-8 (0-63)
 *  @param  y   The y coordinate of the pixel on the CHIP-8 (0-31)
*/
void Chip8Screen::drawPixelAt(const int x, const int y)
{
    int onePixelX = (endX - startX) / 64;
    int onePixelY = (endY - startY) / 32;
    int scaledX = onePixelX * x;
    int scaledY = onePixelY * y;

    float vertices[] = {
        scaledX, scaledY, //Top Left
        scaledX + onePixelX, scaledY, //Top Right
        scaledX + onePixelX, scaledY + onePixelY, // Bottom Right
        scaledX, scaledY + onePixelY // Bottom Left
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 3, 2
    };
    drawRect(vertices, indices, sizeof(vertices), sizeof(indices), pixelShader);
}


void Chip8Screen::handleKeys(const int key, const int scancode, const int action, const int mods)
{
    if(keyMap.find(key) != keyMap.end())
    {
        chip8->keys[keyMap[key]] = action == GLFW_PRESS || action == GLFW_REPEAT ? 1 : 0;
        if(action == GLFW_PRESS && chip8->waitKey != -1)
        {
            chip8->registers[chip8->waitKey] = keyMap[key];
            chip8->waitKey = -1;
        }
    }
}