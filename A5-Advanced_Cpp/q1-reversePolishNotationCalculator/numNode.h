#ifndef NUMNODE_H
#define NUMNODE_H
#include <memory>
#include "expressionNode.h"

class NumNode : public ExpressionNode { // Concrete element
    int num;
    public:
        virtual std::string accept(ExpressionVisitor v);
};

#endif