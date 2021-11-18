#include "tree.h"
using namespace std;

Tree::Tree(std::istringstream &expression_ss, string root_val) { // ctor that builds tree from ss
    // Use corresponding node ctor to build tree from ss
    if (root_val == "+") {
        root = make_unique<PlusNode>(expression_ss);
    } else if (root_val == "-") {
        root = make_unique<MinusNode>(expression_ss);
    } else if (root_val == "*") {
        root = make_unique<MultNode>(expression_ss);
    } else if (root_val == "/") {
        root = make_unique<DivNode>(expression_ss);
    } else { // NumNode otherwise
        root = make_unique<NumNode>(stoi(root_val));
    }
}
Tree::~Tree() {}

ExpressionNode *Tree::getRoot() { return root.get(); }
