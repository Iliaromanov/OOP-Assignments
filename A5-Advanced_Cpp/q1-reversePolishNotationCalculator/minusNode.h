#ifndef MINUSNODE_H
#define MINUSNODE_H
#include <memory>
#include "expressionNode.h"

class MinusNode : public ExpressionNode { // Concrete element
    public:
        virtual std::string accept(ExpressionVisitor &v) override;
        MinusNode(std::istringstream &expression_ss);
};

#endif