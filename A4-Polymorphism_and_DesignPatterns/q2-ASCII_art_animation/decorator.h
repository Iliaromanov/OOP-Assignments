#ifndef DECORATOR_H
#define DECORATOR_H
#include "asciiart.h"
#include <iostream>

class Decorator: public AsciiArt {
    protected:
        AsciiArt *component;
    public:
        Decorator(AsciiArt *component);
        virtual char charAt(int row, int col, int tick) = 0;
        virtual ~Decorator();
}; 

#endif
