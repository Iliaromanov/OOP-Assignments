#include "sequence.h"
#include <iostream>
using namespace std;

int main() {
    Sequence seq{0, {{'s', 0}}};
    char cmd;
    int readIn;

    while (1) {
        // check for eof
        if (cin.eof()) break;

        // Read command and value from stdin
        cin >> cmd;
        cin >> readIn;

        // update the seq struct based on cmd
        switch (cmd) {
            case 's': // if s, then clear the vector and add the s as only func
                seq.x = readIn;
                seq.funcSequence.clear();
                seq.funcSequence.emplace_back('s', readIn);
                break;
            case 'n': // call the updateAndPrintX() method
                seq.updateAndPrintX();
                break;
            default: // Otherwise append cmd to the seq's function sequence
                seq.funcSequence.emplace_back(cmd, readIn);
                break;
        }
    }
}