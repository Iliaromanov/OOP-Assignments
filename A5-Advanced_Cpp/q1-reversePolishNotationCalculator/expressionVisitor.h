#ifndef EXPRVISITOR_H
#define EXPRVISITOR_H
#include "plusNode.h"
#include "minusNode.h"
#include "multNode.h"
#include "divNode.h"
#include "numNode.h"

class ExpressionVisitor { // Visitor abstract base class
    public:
        virtual std::string visit(PlusNode *node) = 0;
        virtual std::string visit(MinusNode *node) = 0;
        virtual std::string visit(MultNode *node) = 0;
        virtual std::string visit(DivNode *node) = 0;
        virtual std::string visit(NumNode *node) = 0;
};

#endif