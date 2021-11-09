#ifndef FILLEDBOX_H
#define FILLEDBOX_H
#include <iostream>
#include "decorator.h"

class Filledbox : public Decorator {
    int top, bottom, left, right;
    char what;

    public:
        Filledbox(int top, int bottom, int left, int right, char what, AsciiArt *component);
        virtual char charAt(int row, int col, int tick) override;
        virtual ~Filledbox();
};

#endif