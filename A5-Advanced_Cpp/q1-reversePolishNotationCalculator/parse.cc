#include "parse.h"
using namespace std;

string Parse::visit(PlusNode *node) {
    return "(" + node->getLeft()->accept(*this) + "+" + node->getRight()->accept(*this) + ")";
}
string Parse::visit(MinusNode *node) {
    return "(" + node->getLeft()->accept(*this) + "-" + node->getRight()->accept(*this) + ")";
}
string Parse::visit(MultNode *node) {
    return "(" + node->getLeft()->accept(*this) + "*" + node->getRight()->accept(*this) + ")";
}
string Parse::visit(DivNode *node) {
    return "(" + node->getLeft()->accept(*this) + "/" + node->getRight()->accept(*this) + ")";
}
string Parse::visit(NumNode *node) {
    return node->getNum();
}

Parse::~Parse() {}