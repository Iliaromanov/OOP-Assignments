#include "plusNode.h"
#include "expressionVisitor.h"
using namespace std;

PlusNode::PlusNode(unique_ptr<ExpressionNode> left, unique_ptr<ExpressionNode> right) 
    : ExpressionNode{move(left), move(right)} {}

std::string PlusNode::accept(ExpressionVisitor &v) {
    return v.visit(this);
}
