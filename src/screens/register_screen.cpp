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
    Color offBlack = { 50, 50, 50, 255 };
    Color gray = { 160, 160, 160, 255 };
    Color blue = { 17, 90, 198, 255 };
    Color orange = { 255, 165, 0, 255};
    Color red = { 255, 0, 0, 255 };

    drawText(5, 20, "Processed Opcode:", offBlack);
    drawText(160, 20, StringHelper::IntToHexString(chip8->currentOpcode), blue);

    drawText(230, 20, "Next Opcode:", offBlack);
    drawText(345, 20, StringHelper::IntToHexString(chip8->nextOpcode), blue);

    if(chip8->opcodeError)
    {
        drawText(420, 20, "OPCODE_ERROR", red);
    }
    else if(chip8->paused)
    {
        drawText(420, 20, "PAUSED", orange);
    }
    else
    {
        drawText(420, 20, "RUNNING", offBlack);
    }

    drawText(5, 35, "------------------------------------------------"
                    "------------------------------------------------", offBlack);
    for(int i = 0; i <= 14; i++)
    {
        int x = 5 + (100 * (i / 3));
        int y = 55 + (25 * (i % 3)); 
        drawText((float) x, (float) y, "R[" + std::to_string(i) + "]", gray);
        drawText((float) x + 45, (float) y, StringHelper::IntToHexString(static_cast<int>(chip8->registers[i]), 2), offBlack);
    }
    
    drawText(520, 70, "rI", gray);
    drawText(545, 70, StringHelper::IntToHexString(static_cast<int>(chip8->iRegister), 4), offBlack);

    drawText(520, 95, "rF", gray);
    drawText(545, 95, StringHelper::IntToHexString(static_cast<int>(chip8->flagRegister), 2), offBlack);

    drawText(620, 70, "tS", gray);
    drawText(645, 70, StringHelper::IntToHexString(static_cast<int>(chip8->timerSound), 2), offBlack);

    drawText(620, 95, "tD", gray);
    drawText(645, 95, StringHelper::IntToHexString(static_cast<int>(chip8->timerDelay), 2), offBlack);
}