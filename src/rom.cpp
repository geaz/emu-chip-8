#include <fstream>

#include "rom.hpp"

Rom::Rom(std::string romPath) : romPath(romPath)
{
    std::ifstream romFile;
    romFile.open(romPath, std::ofstream::binary);

    romFile.seekg(0, romFile.end);
    romLength = (unsigned long) romFile.tellg();
    romFile.seekg(0, romFile.beg);
    
    content = new char[romLength];
    std::cout << "Reading " + romPath + " ... \n";

    romFile.read(content, romLength);
    romFile.close();
}