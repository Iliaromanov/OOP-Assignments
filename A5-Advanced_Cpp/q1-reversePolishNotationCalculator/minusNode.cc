#include "minusNode.h"
#include "expressionVisitor.h"
using namespace std;

MinusNode::MinusNode(unique_ptr<ExpressionNode> left, unique_ptr<ExpressionNode> right) 
    : ExpressionNode{move(left), move(right)} {}

std::string MinusNode::accept(ExpressionVisitor &v) {
    return v.visit(this);
}