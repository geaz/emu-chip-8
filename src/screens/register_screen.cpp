#include <string>
#include <iomanip>
#include <algorithm>

#include "register_screen.h"

RegisterScreen::RegisterScreen(int row, int column, Chip8* chip8) : Screen(row, column), chip8(chip8)
{     
    setClearColor({ 255, 255, 255, 255});
}

void RegisterScreen::draw()
{ 
    // https://tweex.net/post/c-anything-tofrom-a-hex-string/
    std::stringstream hexStringStream; 
    hexStringStream.str(std::string());    
    hexStringStream << std::hex << std::setfill('0');
    hexStringStream << std::setw(4) << static_cast<int>(chip8->currentOpcode);

    std::string hexString = hexStringStream.str();
    std::transform(hexString.begin(), hexString.end(), hexString.begin(), std::toupper);

    drawText(0, 20, "0x" + hexString, { 0, 0, 0, 255});
}