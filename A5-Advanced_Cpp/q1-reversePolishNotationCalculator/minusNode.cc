#include "minusNode.h"
#include "expressionVisitor.h"
using namespace std;

MinusNode::MinusNode(std::istringstream &expression_ss) : ExpressionNode{expression_ss} {} // ctor

std::string MinusNode::accept(ExpressionVisitor &v) {
    return v.visit(this);
}