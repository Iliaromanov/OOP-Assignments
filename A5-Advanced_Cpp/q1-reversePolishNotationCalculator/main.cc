#include "tree.h"
#include "calculate.h"
#include "parse.h"
#include <memory>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string reverse_polish;
    while(getline(cin, reverse_polish)) {
        istringstream ss{reverse_polish};
        Tree expresison_tree{ss};
        Calculate calculator;
        Parse parser;
        unique_ptr<ExpressionNode> root = expresison_tree.getRoot();
        string result = root->accept(calculator);
        string infix_notation = root->accept(parser);
        cout << infix_notation << " = " << result << endl;
    }
}