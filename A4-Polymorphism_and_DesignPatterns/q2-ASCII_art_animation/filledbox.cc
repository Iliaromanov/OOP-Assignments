#include "filledbox.h"

Filledbox::Filledbox(
    int top, int bottom, int left, int right, char what, AsciiArt *component)
    : Decorator{component}, top{top}, bottom{bottom}, left{left}, right{right}, what{what} {}

char Filledbox::charAt(int row, int col, int tick) {
    // if the location is within the boxes bounds, 
    //  then return the char the box is filled with
    if (row >= top && row <= bottom && col >= left && col <= right) {
        return what;
    }
    // otherwise check for boxes on layers below this one
    return component->charAt(row, col, tick);
}

Filledbox::~Filledbox() {}