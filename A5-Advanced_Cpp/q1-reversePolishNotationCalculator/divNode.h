#ifndef DIVNODE_H
#define DIVNODE_H
#include <memory>
#include "expressionNode.h"

class DivNode : public ExpressionNode { // Concrete element
    public:
        virtual std::string accept(ExpressionVisitor v);
};

#endif