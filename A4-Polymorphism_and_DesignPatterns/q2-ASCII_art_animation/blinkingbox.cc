#include "blinkingbox.h"

Blinkingbox::Blinkingbox(
    int top, int bottom, int left, int right, char what, AsciiArt *component)
    : Decorator{component}, top{top}, bottom{bottom}, left{left}, right{right}, what{what} {}

char Blinkingbox::charAt(int row, int col, int tick) {
    // if the location is within the boxes bounds and tick is even, 
    //  then return the char the box is filled with
    if (row >= top && row <= bottom && col >= left && col <= right && !(tick % 2)) {
        return what;
    }
    // otherwise check for boxes on layers below this one
    return component->charAt(row, col, tick);
}

Blinkingbox::~Blinkingbox() {}