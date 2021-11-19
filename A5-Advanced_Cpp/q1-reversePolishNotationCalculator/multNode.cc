#include "multNode.h"
#include "expressionVisitor.h"
using namespace std;

MultNode::MultNode(unique_ptr<ExpressionNode> left, unique_ptr<ExpressionNode> right) 
    : ExpressionNode{move(left), move(right)} {}

std::string MultNode::accept(ExpressionVisitor &v) {
    return v.visit(this);
}