#include "plusNode.h"
#include "expressionVisitor.h"
using namespace std;

PlusNode::PlusNode(std::istringstream &expression_ss) : ExpressionNode{expression_ss} {} // ctor

std::string PlusNode::accept(ExpressionVisitor &v) {
    return v.visit(this);
}
