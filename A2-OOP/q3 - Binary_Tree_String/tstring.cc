#include "tstring.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


TString::TNode::TNode(string s, int size, TNode *left, TNode *right, TNode *parent) { // TNode ctor
    this->data = s;
    this->size = size;
    this->left = left;
    this->right = right;
    this->parent = parent;
}

TString::TNode::TNode(const TNode &other, TNode *parent) { // TNode deep copy method, (not sure if it can be called a copy ctor)
    this->data = other.data; // seg fault here, cus this=nullptr.
    this->size = other.size;
    this->left = other.left ? new TNode{*other.left, this} : nullptr;
    this->right = other.right ? new TNode{*other.right, this} : nullptr;
    this->parent = parent;
}

TString::TNode::~TNode() { // TNode destructor
    delete left;
    delete right;
}

std::ostream& operator<<(std::ostream& out, const TString::TNode &node) {
    if (!node.left) {
        out << node.data;
    } else {
        out << *node.left;
        out << node.data;
    }
    if (node.right) out << *node.right;

    return out;
}

void TString::TNode::updateSizes(int amount) {
    size += amount;
    if (parent) {
        if (parent->left == this) {
            parent->updateSizes(amount);
        } else {
            TNode *firstLeftPar = this->firstLeftParent();
            if (firstLeftPar) firstLeftPar->updateSizes(amount);
        }
    }
}

TString::TNode *TString::TNode::firstLeftParent() {
    if (!parent) return nullptr;
    if (parent->left == this) return parent;
    return parent->firstLeftParent();
}

void TString::TNode::NodeInsert(const std::string &s, const int i) {
    if (s == "") return; // tree is unchanged when inserting empty string
    if (data == "") {
        data = s;
        size = s.length();
        return;
    }

    if (size - data.length() > i) {
        left->NodeInsert(s, i); // insert into left subtree
    } else if (size - data.length() == i) {
        if (left) {
            left->NodeInsert(s, i); // insert at end of left child
        } else {
            this->updateSizes(s.length()); // increase size of all parents by s.length()
            left = new TNode{s, s.length(), nullptr, nullptr, this}; // insert as the left child
        }
    } else if (size <= i) {
        if (right) {
            right->NodeInsert(s, i - size); // insert into right subtree
        } else {
            TNode *firstLeftPar = this->firstLeftParent();
            if (firstLeftPar) {
                // increse size of first parent that has this node in its left subtree, 
                //  and increase size of that nodes parents
                firstLeftPar->updateSizes(s.length());
            }
            right = new TNode{s, s.length(), nullptr, nullptr, this}; // insert as the right child
        }
    } else { // size - data.length() < i < size; need to split
        TNode *old_left = left;
        TNode *old_right = right;
        string new_left_s = data.substr(0, i-(size-data.length()));
        string new_right_s = data.substr(i-(size-data.length()), data.length());
        left = new TNode{new_left_s, i, old_left, nullptr, this};;
        right = new TNode{new_right_s, size-i, nullptr, old_right, this};
        data = s;
        size = i + s.length();
        if (parent) { // update parent sizes accordingly
            if (parent->left == this) { // curent node is a left child
                parent->updateSizes(s.length());
            } else { // current node is a right child
                TNode *firstLeftPar = this->firstLeftParent();
                if (firstLeftPar) firstLeftPar->updateSizes(s.length());
            }
        }
    }
}

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

TString::TNode *TString::TNode::RmAndReturnRightmostChild() {
    if (!right) {
        if (parent) parent->right = nullptr; // remove it from tree, if its not the root node
        return this;
    } else {
        return right->RmAndReturnRightmostChild();
    }
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
    TNode *new_root_old_left = new_root->left; // i was gonna use this to cover the edge case where the rightmost child 
    // has a left child, but I literally had an assignment due for every one of my 4 other courses + a midterm all in the last two days
    // + I have a fever and I'm dying rn, sorry

    new_root->size = t1_root_copy->size - t1_root_copy->data.length() + new_root->data.length();
    new_root->left = t1_root_copy;
    new_root->right = t2_root_copy;
    new_root->parent = nullptr;

    result.root = new_root;

    return result;
}

char &TString::TNode::operator[](const int i) {
    if (size - data.length() > i) {
        return (*left)[i];
    } else if (size - data.length() == i) {
        return data[0];
    } else if (size <= i) {
        return (*right)[i - size];
    } else { // size - data.length() < i < size
        return data[i-(size-data.length())];
    }
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
                    if (p) ind = 0;
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

TString::TNode* TString::TNode::leftmostNode() {
    if (!left) return this;
    return left->leftmostNode();
}

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