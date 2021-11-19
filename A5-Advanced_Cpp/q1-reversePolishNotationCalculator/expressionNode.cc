#include "expressionNode.h"
#include "expressionVisitor.h"
using namespace std;

ExpressionNode::ExpressionNode() : left{nullptr}, right{nullptr} {} // default ctor

ExpressionNode::ExpressionNode(istringstream &expression_ss) { // ctor for building tree from ss
    string right_val;
    string left_val;
    expression_ss >> right_val;
    expression_ss >> left_val;

    // build right subtree
    if (right_val == "+") {
        right = make_unique<PlusNode>(expression_ss);
    } else if (right_val == "-") {
        right = make_unique<MinusNode>(expression_ss);
    } else if (right_val == "*") {
        right = make_unique<MultNode>(expression_ss);
    } else if (right_val == "/") {
        right = make_unique<DivNode>(expression_ss);
    } else { // NumNode otherwise
        right = make_unique<NumNode>(right_val);
    }

    // build left subtree
    if (left_val == "+") {
        left = make_unique<PlusNode>(expression_ss);
    } else if (left_val == "-") {
        left = make_unique<MinusNode>(expression_ss);
    } else if (left_val == "*") {
        left = make_unique<MultNode>(expression_ss);
    } else if (left_val == "/") {
        left = make_unique<DivNode>(expression_ss);
    } else { // NumNode otherwise
        left = make_unique<NumNode>(right_val);
    }
}

// getters
ExpressionNode *ExpressionNode::getLeft() { return left.get(); }
ExpressionNode *ExpressionNode::getRight() { return right.get(); }

// destructor
ExpressionNode::~ExpressionNode() {};