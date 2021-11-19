#include "calculate.h"
using namespace std;

string Calculate::visit(PlusNode *node) {
    return to_string(stoi(node->getLeft()->accept(*this)) + stoi(node->getRight()->accept(*this)));
}
string Calculate::visit(MinusNode *node) {
    return to_string(stoi(node->getLeft()->accept(*this)) - stoi(node->getRight()->accept(*this)));
}
string Calculate::visit(MultNode *node) {
    return to_string(stoi(node->getLeft()->accept(*this)) * stoi(node->getRight()->accept(*this)));
}
string Calculate::visit(DivNode *node) {
    return to_string(stoi(node->getLeft()->accept(*this)) / stoi(node->getRight()->accept(*this)));
}
string Calculate::visit(NumNode *node) {
    return node->getNum();
}

Calculate::~Calculate() {}