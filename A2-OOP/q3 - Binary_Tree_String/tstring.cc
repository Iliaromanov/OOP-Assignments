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

std::ostream& operator<<(std::ostream& out, const TString::TNode &node) { //---------------------------------------- PRINT BROOOOOOOOKKEEEEEEEEENNNNNNNN
    if (!node.left) { // if left = nullptr
        out << node.data;
    } else {
        if (node.left) out << *node.left;
    }
    if (node.right) out << *node.right;
    out << node.data;

    return out;
}

void TString::TNode::updateSizes(int amount, bool from_right) {
    cout << data << "| " << "cur size: " << size << endl;
    cout << " amount: " << amount << endl;
    if (from_right) {
        size = data.length() + amount; // -----------------------------FROM RIGHT WRONG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    } else {
        size += amount;
    }
    cout << "new size: " << size << endl;
    if (parent) {
        parent->updateSizes(amount, false); // the rest would be frm left
    }
}

void TString::TNode::NodeInsert(const std::string &s, const int i) {
    if (size - data.length() > i) {
        left->NodeInsert(s, i); // insert into left subtree
    } else if (size <= i) {
        right->NodeInsert(s, i - size); // insert into right subtree
    } else if (size - data.length() == i) {
        if (left) {
            left->NodeInsert(s, left->size - 1); // insert at end of left child
        } else {
            cout << "updating parents of: " << s << endl;
            this->updateSizes(s.length(), false); // increase size of all parents by s.length()
            cout << "~~~~~~~~" << endl;
            left = new TNode{s, s.length(), nullptr, nullptr, this}; // insert as the left child
        }
    } else if (size - 1 == i) {
        if (right) {
            right->NodeInsert(s, right->size - right->data.length()); // insert at start of right child
        } else {
            if (parent) {
                cout << "updating parents of: " << s << endl;
                parent->updateSizes(s.length() + data.length(), true); // increse size of parent's parents
            }
            cout << "~~~~~~~~" << endl;
            right = new TNode{s, s.length(), nullptr, nullptr, this}; // insert as the right child
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