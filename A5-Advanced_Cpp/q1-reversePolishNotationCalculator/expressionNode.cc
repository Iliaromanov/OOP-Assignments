#include "expressionNode.h"
#include "expressionVisitor.h"
using namespace std;


ExpressionNode::ExpressionNode() : left{nullptr}, right{nullptr} {} // default ctor

// ctor that takes left and right child nodes
ExpressionNode::ExpressionNode(unique_ptr<ExpressionNode> left, unique_ptr<ExpressionNode> right) 
    : left{move(left)}, right{move(right)} {}

// getters
ExpressionNode *ExpressionNode::getLeft() { return left.get(); }
ExpressionNode *ExpressionNode::getRight() { return right.get(); }

// destructor
ExpressionNode::~ExpressionNode() {};