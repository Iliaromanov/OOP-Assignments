#ifndef EXPRNODE_H
#define EXPRNODE_H
#include <memory>
#include <string>

class ExpressionVisitor;

class ExpressionNode { // Element abstract base class
    std::unique_ptr<ExpressionNode> left;
    std::unique_ptr<ExpressionNode> right;
    public:
        ExpressionNode();
        ExpressionNode(std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right);
        ~ExpressionNode();
        ExpressionNode *getLeft();
        ExpressionNode *getRight();
        virtual std::string accept(ExpressionVisitor &v) = 0;
};

#endif