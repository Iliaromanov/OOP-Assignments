#ifndef TREE_H
#define TREE_H
#include <memory>
#include <sstream>
#include "expressionNode.h"

class Tree {
    std::unique_ptr<ExpressionNode> root;
    public:
        ExpressionNode *getRoot();
        Tree(std::istringstream &expression_ss, string root_val); // ctor that builds tree from ss
        ~Tree();
};

#endif
