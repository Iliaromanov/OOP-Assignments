#include <iostream>
#include "sequence.h"
using namespace std;

void Sequence::updateAndPrintX() {
    int result = x;
    for (auto func : funcSequence) {
        switch (func.operation) {
            case 's':
                // do nothing since its identity func
                break;
            case '+':
                result += func.readIn;
                break;
            case '-':
                result -= func.readIn;
                break;
            case '*':
                result *= func.readIn;
                break;
            case '/':
                result /= func.readIn;
                break;
        }
    }
    x = result;
    cout << result << endl;
}