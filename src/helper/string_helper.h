#pragma once
#ifndef STRING_H
#define STRIN_H

#include <string>

class StringHelper
{
    public:
        static std::string IntToHexString(const int data, int stringWidth = 4);
};

#endif // STRING_H