#ifndef CALC_H
#define CALC_H
#include "expressionVisitor.h"

class Calculate : public ExpressionVisitor { // Concrete visitor
    public:
        std::string visit(PlusNode *node) override;
        std::string visit(MinusNode *node) override;
        std::string visit(MultNode *node) override;
        std::string visit(DivNode *node) override;
        std::string visit(NumNode *node) override;
        ~Calculate();
};

#endif