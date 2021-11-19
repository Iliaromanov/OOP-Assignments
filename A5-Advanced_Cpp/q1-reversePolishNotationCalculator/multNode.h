#ifndef MULTNODE_H
#define MULTNODE_H
#include <memory>
#include "expressionNode.h"

class MultNode : public ExpressionNode { // Concrete element
    public:
        virtual std::string accept(ExpressionVisitor &v) override;
        MultNode(std::istringstream &expression_ss);
};

#endif