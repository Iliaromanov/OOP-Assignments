#include "movingbox.h"

Movingbox::Movingbox(
    int top, int bottom, int left, int right, char what, char dir, AsciiArt *component)
    : Decorator{component}, top{top}, bottom{bottom}, left{left}, right{right}, what{what}, dir{dir} {}

char Movingbox::charAt(int row, int col, int tick) {
    // calculate the shift values based on tick
    int deltaY = 0;
    int deltaX = 0;
    switch (dir) {
        case 'l':
            deltaX = -1 * tick;
            break;
        case 'r': 
            deltaX = 1 * tick;
            break;
        case 'd':
            deltaY = 1 * tick;
            break;
        case 'u':
            deltaY = -1 * tick;
            break;
    }

    // if the location considering shift is within the boxes bounds, 
    //  then return the char the box is filled with
    if (row >= top + deltaY && row <= bottom + deltaY && col >= left + deltaX && col <= right + deltaX) {
        return what;
    }
    // otherwise check for boxes on layers below this one
    return component->charAt(row, col, tick);
}

Movingbox::~Movingbox() {}