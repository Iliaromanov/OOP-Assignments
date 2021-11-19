#include "tree.h"
#include "plusNode.h"
#include "minusNode.h"
#include "multNode.h"
#include "divNode.h"
#include "numNode.h"
#include <iostream>
using namespace std;

Tree::Tree() : root{make_unique<NumNode>("0")} {} // default ctor

void Tree::BuildTree(std::istringstream &expression_ss, string node_val) {
    string ops = "+-*/";
    if (ops.find(node_val) != string::npos) { // node is an operation
        auto right = move(stack.back());
        stack.pop_back();
        auto left = move(stack.back());
        stack.pop_back();
        if (node_val == "+") {
            stack.push_back(make_unique<PlusNode>(move(left), move(right)));
        } else if (node_val == "-") {
            stack.push_back(make_unique<MinusNode>(move(left), move(right)));
        } else if (node_val == "*") {
            stack.push_back(make_unique<MultNode>(move(left), move(right)));
        } else if (node_val == "/") {
            stack.push_back(make_unique<DivNode>(move(left), move(right)));
        }
    } else { // NumNode otherwise
        stack.push_back(make_unique<NumNode>(node_val));
    }

    // if eof, then we just pushed root onto the stack
    if (expression_ss.eof()) {
        // When the end of the expression is reached 
        //   there must only be one node on the stack, otherwise invalid
        if (stack.size() != 1) { cout << "Invalid Expression!" << endl; exit(1); }
        root = move(stack.back());
        stack.pop_back();
        return;
    }

    // read in next node for ss and build the rest of the tree
    string next_val;
    expression_ss >> next_val;
    BuildTree(expression_ss, next_val);
}

Tree::~Tree() {}

ExpressionNode *Tree::getRoot() { return root.get(); }
