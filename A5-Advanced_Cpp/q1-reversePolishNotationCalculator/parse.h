#ifndef PARSE_H
#define PARSE_H
#include "plusNode.h"
#include "minusNode.h"
#include "multNode.h"
#include "divNode.h"
#include "numNode.h"

class Parse : public ExpressionVisitor { // Concrete visitor
    public:
        std::string visit(PlusNode *node);
        std::string visit(MinusNode *node);
        std::string visit(MultNode *node);
        std::string visit(DivNode *node);
        std::string visit(NumNode *node);
};

#endif