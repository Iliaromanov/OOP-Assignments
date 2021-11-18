#include "tree.h"
#include "calculate.h"
#include "parse.h"
#include <memory>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string rev_polish_notation;
    while(getline(cin, rev_polish_notation)) {
        // reverse the read line, then convert to string stream
        reverse(rev_polish_notation.begin(), rev_polish_notation.end());
        istringstream ss{rev_polish_notation};

        // get root node value
        string root_val;
        ss >> root_val;
        // string root_val = rev_polish_notation.substr(0, rev_polish_notation.find(' '));

        // call tree ctor
        Tree expresison_tree{ss, root_val};

        // create visitor objects
        Calculate calculator;
        Parse parser;

        // visit the tree with both visitors
        ExpressionNode *root = expresison_tree.getRoot();
        string result = root->accept(calculator);
        string infix_notation = root->accept(parser);
        cout << infix_notation << " = " << result << endl;
    }
}