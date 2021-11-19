#include "numNode.h"
#include "expressionVisitor.h"
using namespace std;

NumNode::NumNode(std::string num) : num{num} {}
string NumNode::getNum() { return num; }
string NumNode::accept(ExpressionVisitor &v) {
    return v.visit(this);
}