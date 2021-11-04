#include "sequence.h"
#include <iostream>
using namespace std;

int main() {
    Sequence seq{0, {{'s', 0}}};
    char cmd;
    int readIn;

    while (1) {
        // Read command and value from stdin
        cin >> cmd;
        // check for eof
        if (cin.eof()) break;

        // n command
        if (cmd == 'n') {
            seq.updateAndPrintX();
            continue; // no need to read in an int
        }
        cin >> readIn;

        // if s, then clear the vector and add the s as only func in func sequence
        if (cmd == 's') { 
            seq.x = readIn;
            seq.funcSequence.clear();
            seq.funcSequence.emplace_back('s', readIn);
        // Otherwise append cmd to the seq's function sequence
        } else {
            seq.funcSequence.emplace_back(cmd, readIn);
        }
    }
}