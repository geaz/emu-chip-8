#include "chip8_screen.h"

Chip8Screen::Chip8Screen(int row, int column, Chip8* chip8) : Screen(row, column), chip8(chip8)
{ }

void Chip8Screen::draw()
{ 
    chip8->processCycle();
}