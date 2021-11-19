#ifndef PARSE_H
#define PARSE_H
#include "expressionVisitor.h"
#include "plusNode.h"
#include "minusNode.h"
#include "multNode.h"
#include "divNode.h"
#include "numNode.h"

class Parse : public ExpressionVisitor { // Concrete visitor
    public:
        std::string visit(PlusNode *node) override;
        std::string visit(MinusNode *node) override;
        std::string visit(MultNode *node) override;
        std::string visit(DivNode *node) override;
        std::string visit(NumNode *node) override;
        ~Parse();
};

#endif