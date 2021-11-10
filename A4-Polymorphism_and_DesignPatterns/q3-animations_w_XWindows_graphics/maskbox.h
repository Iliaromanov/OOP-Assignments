#ifndef MASK_H
#define MASK_H
#include <iostream>
#include "decorator.h"

class Maskbox : public Decorator {
    int top, bottom, left, right;
    char what;

    public:
        Maskbox(int top, int bottom, int left, int right, char what, AsciiArt *component);
        virtual char charAt(int row, int col, int tick) override;
        virtual ~Maskbox();
};

#endif