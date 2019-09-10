#pragma once
#ifndef ROM_H
#define ROM_H

#include <iostream>

class Rom
{
    public:
        Rom(const std::string romPath);

        std::string romPath;
        long romLength;
        char* content;
};

#endif // ROM_H