#include "maskbox.h"

Maskbox::Maskbox(
    int top, int bottom, int left, int right, char what, AsciiArt *component)
    : Decorator{component}, top{top}, bottom{bottom}, left{left}, right{right}, what{what} {}

char Maskbox::charAt(int row, int col, int tick) {
    // if the location is within the boxes bounds, and there is a box below it
    //  then return the char the box is filled with
    if (row >= top && row <= bottom && col >= left && col <= right
        && component->charAt(row, col, tick) != ' ') {
        return what;
    }
    // otherwise there are no boxes under this box and can just return ' '
    return ' ';
}

Maskbox::~Maskbox() {}