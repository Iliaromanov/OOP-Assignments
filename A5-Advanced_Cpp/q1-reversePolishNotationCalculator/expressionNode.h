#ifndef EXPRNODE_H
#define EXPRNODE_H
#include <sstream>
#include <memory>
#include <string>

class ExpressionVisitor;

class ExpressionNode { // Element abstract base class
    std::unique_ptr<ExpressionNode> left;
    std::unique_ptr<ExpressionNode> right;
    public:
        ExpressionNode *getLeft();
        ExpressionNode *getRight();
        virtual std::string accept(ExpressionVisitor &v) = 0;
        ExpressionNode();
        ExpressionNode(std::istringstream &expression_ss);
        ~ExpressionNode();
};

#endif