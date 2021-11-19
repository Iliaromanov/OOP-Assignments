#include "divNode.h"
#include "expressionVisitor.h"
using namespace std;


DivNode::DivNode(unique_ptr<ExpressionNode> left, unique_ptr<ExpressionNode> right) 
    : ExpressionNode{move(left), move(right)} {}

std::string DivNode::accept(ExpressionVisitor &v) {
    return v.visit(this);
}