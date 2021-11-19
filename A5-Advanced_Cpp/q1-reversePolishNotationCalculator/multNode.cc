#include "multNode.h"
#include "expressionVisitor.h"
using namespace std;

MultNode::MultNode(std::istringstream &expression_ss) : ExpressionNode{expression_ss} {} // ctor

std::string MultNode::accept(ExpressionVisitor &v) {
    return v.visit(this);
}