#ifndef TREE_H
#define TREE_H
#include <memory>
#include <sstream>
#include "expressionNode.h"
#include <string>
#include <vector>

class Tree {
    std::unique_ptr<ExpressionNode> root;
    std::vector<std::unique_ptr<ExpressionNode>> stack;
    public:
        Tree();
        ~Tree();
        // method that builds tree from ss
        void BuildTree(std::istringstream &expression_ss, std::string root_val);
        // getter for root node
        ExpressionNode *getRoot();
};

#endif
