#ifndef SEQ_H
#define SEQ_H
#include <vector>
struct Func {
    char operation; // one of 's', '+', '-', '*', '/'
    int readIn;
};
struct Sequence {
    int x;
    std::vector<Func> funcSequence;
    // applies the current function to x
    void updateAndPrintX();
};
#endif