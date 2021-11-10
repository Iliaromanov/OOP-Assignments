#ifndef BLINKING_H
#define BLINKING_H
#include <iostream>
#include "decorator.h"

class Blinkingbox : public Decorator {
    int top, bottom, left, right;
    char what;

    public:
        Blinkingbox(int top, int bottom, int left, int right, char what, AsciiArt *component);
        virtual char charAt(int row, int col, int tick) override;
        virtual ~Blinkingbox();
};

#endif