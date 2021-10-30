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
    data = other.data;
    size = other.size;
    left = new TNode{*other.left, this};
    left = new TNode{*other.right, this};
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

    // cout << "this: '" << data << "' size: " << size << " | inserting: '" << s << "' at: " << i << endl;


    if (size - data.length() > i) {
        left->NodeInsert(s, i); // insert into left subtree
    } else if (size - data.length() == i) {
        if (left) {
            left->NodeInsert(s, i); // insert at end of left child
        } else {

            // cout << "updating parents of: " << s << endl;

            this->updateSizes(s.length()); // increase size of all parents by s.length()

            // cout << "~~~~~~~~" << endl;

            left = new TNode{s, s.length(), nullptr, nullptr, this}; // insert as the left child
        }
    } else if (size <= i) {
        if (right) {
            right->NodeInsert(s, i - size); // insert into right subtree
        } else {
            TNode *firstLeftPar = this->firstLeftParent();
            if (firstLeftPar) {

                // cout << "updating parents of: " << s << endl;

                // increse size of first parent that has this node in its left subtree, 
                //  and increase size of that nodes parents
                firstLeftPar->updateSizes(s.length());
            }

            // cout << "~~~~~~~~" << endl;

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
    length = length;
    root = new TNode{*root, nullptr}; // call the TNode copy ctor
}

TString::~TString() { // TString destructor
    delete root; // invoke added tnode destructor
}

TString TString::operator+( const TString & t) const {
    // Get rightmost child
}
char& TString::operator[] (const int index) {

    // placeholder
    return root->data[0];
}

void TString::insert(const string & s, const int index) {
    this->root->NodeInsert(s, index);
}


std::ostream& operator<<(std::ostream& out, const TString &t) {
    out << *t.root; // use added TNode operator<< override                        
    return out;
}

char &TString::TStringIter::operator*() {

}

TString::TStringIter &TString::TStringIter::operator++() {

}

bool TString::TStringIter::operator!=(const TString::TStringIter &other) {

}

TString::TStringIter::TStringIter(TString::TNode *p, int ind) {

}

TString::TStringIter TString::begin() {

}

TString::TStringIter TString::end() {

}