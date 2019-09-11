#include <string>
#include <iomanip>
#include <algorithm>

#include "register_screen.h"
#include "../helper/string_helper.h"

RegisterScreen::RegisterScreen(int row, int column, Chip8* chip8) : Screen(row, column), chip8(chip8)
{     
    setClearColor({ 255, 255, 255, 255});
}

void RegisterScreen::draw()
{ 
    drawText(0, 20, StringHelper::IntToHexString(chip8->currentOpcode), { 0, 0, 0, 255});
}