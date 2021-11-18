#include "expressionNode.h"

ExpressionNode *ExpressionNode::getLeft() { return left.get(); }
ExpressionNode *ExpressionNode::getRight() { return right.get(); }
ExpressionNode::~ExpressionNode() {};