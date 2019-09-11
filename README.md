# A CHIP-8 emulator written in C++ (WIP)

This project was done to learn how to write a simple emulator, get a bettter understanding of CPUs and to learn a bit of C++.

Because I wanted to show some debug information, I was forced to learn a bit of OpenGL (core mode), too.
I wrote a small "screen" framework for OpenGL. The CHIP-8 output, memory debugger and register debugger are all
seperate "screens", added to the OpenGL window by defining a simple grid layout. The grid layout is very naive,
but enough to be used by this application. It also includes a simple resource manager to load shaders and fonts. 
The font class contains a method to render text and uses *stb_truetype* to create a bitmap of the font file.

This emulator should run cross platform. Use CMAKE to compile it and run it with the roms in the *roms* folder.

Usage example (Windows):  
```
emu-chip-8.exe roms/BRIX
```

## Ressources
- http://learnopengl.com
- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM