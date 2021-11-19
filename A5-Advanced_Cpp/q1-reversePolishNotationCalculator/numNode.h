#ifndef NUMNODE_H
#define NUMNODE_H
#include <memory>
#include "expressionNode.h"

class NumNode : public ExpressionNode { // Concrete element
    std::string num;
    public:
        std::string getNum();
        virtual std::string accept(ExpressionVisitor &v) override;
        NumNode(std::string num);
};

#endif