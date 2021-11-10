#include <iostream>
#include "textObserver.h"
using namespace std;

TextObserver::TextObserver(
    Studio *canvas, int top, int bottom, int left, int right)
    : subject{canvas}, top{top}, bottom{bottom}, left{left}, right{right} 
{
        // subject->attach(this);
}

TextObserver::~TextObserver() {
    subject->detach(this);
}

void TextObserver::notify() {
    cout << '+';
    for (int j = left; j <= right; ++j) cout << '-';
    cout << '+' << std::endl;
    for (int i = top; i <= bottom; ++i) {
        cout << '|';
        for (int j = left; j <= right; ++j) {
            cout << subject->getState(i, j);
        }
        cout << '|' << std::endl;
    }
    cout << '+';
    for (int j = left; j <= right; ++j) cout << '-';
    cout << '+' << std::endl;
}