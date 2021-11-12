#include <iostream>
#include "graphicalObserver.h"
using namespace std;

GraphicalObserver::GraphicalObserver( //ctor
    Studio *canvas, Xwindow *window, int top, int bottom, int left, int right)
    : subject{canvas}, window{window}, top{top}, bottom{bottom}, left{left}, right{right} {}

GraphicalObserver::~GraphicalObserver() { //destructor
    delete window;
    subject->detach(this);
}

void GraphicalObserver::notify() {
    int k = top; // for keeping track of actual row num

    // loop over grid in steps of 10px at a time
    for (int i = top * 10; i <= bottom * 10; i += 10) {
        int l = left; // for keeping track of actual col num
        for (int j = left * 10; j <= right * 10; j += 10) {
            const char c = subject->getState(k, l);
            if (97 <= c && c <= 122) {
                window->fillRectangle(
                    j - (left * 10), i - (top * 10), 10, 10, Xwindow::Red
                );
            } else if (65 <= c && c <= 90) {
                window->fillRectangle(
                    j - (left * 10), i - (top * 10), 10, 10, Xwindow::Green
                );
            } else if (48 <= c && c <= 57) {
                window->fillRectangle(
                    j - (left * 10), i - (top * 10), 10, 10, Xwindow::Blue
                );
            } else if (c == ' ') {
                window->fillRectangle(
                    j - (left * 10), i - (top * 10), 10, 10, Xwindow::White
                );
            } else {
                window->fillRectangle(
                    j - (left * 10), i - (top * 10), 10, 10, Xwindow::Black
                );
            }
            ++l;
        }
        ++k;
    }
}