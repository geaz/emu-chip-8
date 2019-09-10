#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include "../opengl/screen.h"

class Display : public Screen
{   
    public:
        Display(int row, int column);

        void draw();
};

#endif // DISPLAY_H