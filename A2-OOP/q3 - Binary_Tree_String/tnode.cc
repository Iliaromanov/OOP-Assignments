

// IDK IF THERE IS A POINT OF MAKING A SEPARATE FILE FOR THIS 
// IF GETS TOO MESSY WILL USE THIS

#include "tstring.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

TString::TNode::TNode(string s, TNode *left, TNode *right, TNode *parent) {
    this->data = s;
    this->size = s.length();
    this->left = left;
    this->right = right;
    this->parent = parent;
}

TString::TNode::~TNode() {
    delete left;
    delete right;
}
