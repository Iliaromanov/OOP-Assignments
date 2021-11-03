// implementations of TString related operations
#include "tstring.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


TString::TString(const string &s) { // TString ctor
    root = new TNode{s, s.length(), nullptr, nullptr, nullptr};
    length = s.length();
}

TString::TString(const TString & t) { // TString copy ctor
    length = t.length; 
    root = new TNode{*t.root, nullptr}; // call the TNode copy ctor
}

TString::~TString() { // TString destructor
    delete root; // invoke added tnode destructor
}

TString TString::operator+( const TString & t) const {
    TString result = TString{""};
    delete result.root; // free the useless root from ctor
    result.length = this->length + t.length;

    // Make copies of lhs and rhs
    TNode *t1_root_copy = new TNode{*this->root, nullptr};
    if (t.root->data == "") { // if t2 is empty, just return t1 copy
        result.root = t1_root_copy;
        return result;
    }
    TNode *t2_root_copy = new TNode{*t.root, nullptr};
    if (root->data == "") { // if t1 is empty, just return t2 copy
        delete t1_root_copy;
        result.root = t2_root_copy;
        return result;
    }
    
    // if t1 has no right children, it becomes the new root
    if (!t1_root_copy->right) {
        t1_root_copy->right = t2_root_copy;
        result.root = t1_root_copy;
        return result;
    }

    // Otherwise get rightmost child of t1, at the same time removing it from t1; this will be the new root
    TNode *new_root = t1_root_copy->RmAndReturnRightmostChild();
    TNode *new_root_old_left = new_root->left;

    // get the sum of the sizes of the remaining right children of t1 to add to the size of new_root
    int t1_sum_right_nodes = t1_root_copy->right ? t1_root_copy->right->sumRightNodes() : 0;
    new_root->size = t1_root_copy->size + t1_sum_right_nodes + new_root->data.length();

    new_root->left = t1_root_copy;
    new_root->right = t2_root_copy;
    new_root->parent = nullptr;

    result.root = new_root;

    return result;
}

char& TString::operator[] (const int index) {
    return (*root)[index];
}

void TString::insert(const string & s, const int index) {
    root->NodeInsert(s, index);
}


std::ostream& operator<<(std::ostream& out, const TString &t) {
    out << *t.root; // use added TNode operator<< override                        
    return out;
}

char &TString::TStringIter::operator*() {
    return p->data[ind];
}

TString::TStringIter &TString::TStringIter::operator++() {
    ++ind;
    if (ind == p->data.length()) {
        if (p->right) {
            // FIND p->rights leftmost child
            if (p->right->left) {
                p = p->right->leftmostNode();
            } else {
                p = p->right;
            }
            ind = 0;
        } else {
            if (p->parent) {
                if (p->parent->right == p) {
                    p = p->firstLeftParent();
                    if (p) {
                        ind = 0;
                    }
                    // otherwise ind would be ++ind which is the righmost node's size
                } else {
                    p = p->parent;
                    ind = 0;
                }
            } else {
                p = nullptr;
                // and ind would be rightmost.data.lenth()
            }
        }
    }
    return *this;
}

bool TString::TStringIter::operator!=(const TString::TStringIter &other) {
    return !(ind == other.ind && this->p == other.p);
}

TString::TStringIter::TStringIter(TString::TNode *p, int ind) : p{p}, ind{ind} {}

TString::TStringIter TString::begin() {
    int ind = 0;
    TNode *leftmost = root->leftmostNode();
    return TString::TStringIter{leftmost, ind};
}

TString::TNode* TString::TNode::rightmostNode() {
    if (!right) return this;
    return right->rightmostNode();
}

TString::TStringIter TString::end() {
    TNode *rightmost = root->rightmostNode();
    int ind = rightmost->data.length();
    return TString::TStringIter{nullptr, ind};
}