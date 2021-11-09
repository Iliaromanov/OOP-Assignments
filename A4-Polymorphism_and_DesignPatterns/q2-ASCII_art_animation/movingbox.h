#ifndef MOVING_H
#define MOVING_H
#include <iostream>
#include "decorator.h"

class Movingbox : public Decorator {
    int top, bottom, left, right;
    char what, dir;

    public:
        Movingbox(int top, int bottom, int left, int right, char what, char dir, AsciiArt *component);
        virtual char charAt(int row, int col, int tick) override;
        virtual ~Movingbox();
};

#endif