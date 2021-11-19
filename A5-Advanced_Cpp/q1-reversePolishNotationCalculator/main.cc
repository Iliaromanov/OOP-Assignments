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
        // convert to ss so it can be used recursively by BuildTree
        istringstream ss{rev_polish_notation};

        // get first node value
        string first_val;
        ss >> first_val;

        Tree expresison_tree{}; // intizlize tree to placeholder
        expresison_tree.BuildTree(ss, first_val); // build the tree from ss

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