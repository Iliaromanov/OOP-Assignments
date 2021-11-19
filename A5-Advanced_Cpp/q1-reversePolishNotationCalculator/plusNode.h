#ifndef PLUSNODE_H
#define PLUSNODE_H
#include <memory>
#include "expressionNode.h"

class PlusNode : public ExpressionNode { // Concrete element
    public:
        virtual std::string accept(ExpressionVisitor &v) override;
        PlusNode(std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right);
};

#endif