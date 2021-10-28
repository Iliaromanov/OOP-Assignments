#include "tstring.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


TString::TNode::TNode(string s, TNode *left, TNode *right, TNode *parent) { // TNode ctor
    this->data = s;
    this->size = s.length();
    this->left = left;
    this->right = right;
    this->parent = parent;
}

TString::TNode::TNode(const TNode &other, TNode *parent) { // TNode copy ctor
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

TString::TString(const string &s) { // TString ctor
    root = new TNode{s, nullptr, nullptr, nullptr};
    length = s.length();
}

TString::TString(const TString & t) { // TString copy ctor
    length = length;
    root = new TNode{*root, nullptr}; // call the TNode copy ctor
}

TString::~TString() { // TString destructor
    delete root; // pls can the tnode destuctor take care of the rest
}

TString TString::operator+( const TString & t) const {

}
char& TString::operator[] (const int index) {

}

void TString::insert(const string & s, const int index) {

}


std::ostream& operator<<(std::ostream& out, const TString &t) {

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