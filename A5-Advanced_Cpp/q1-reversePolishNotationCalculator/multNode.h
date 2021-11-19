#ifndef MULTNODE_H
#define MULTNODE_H
#include <memory>
#include "expressionNode.h"

class MultNode : public ExpressionNode { // Concrete element
    public:
        virtual std::string accept(ExpressionVisitor &v) override;
        MultNode(std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right);
};

#endif