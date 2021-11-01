// implementations of TNode related operations
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

TString::TNode *TString::TNode::RmAndReturnRightmostChild() {
    if (!right) {
        if (parent) parent->right = nullptr; // remove it from tree, if its not the root node
        return this;
    } else {
        return right->RmAndReturnRightmostChild();
    }
}

int TString::TNode::sumRightNodes() {
    if (!right) return size;
    return size + right->sumRightNodes();
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

TString::TNode* TString::TNode::leftmostNode() {
    if (!left) return this;
    return left->leftmostNode();
}