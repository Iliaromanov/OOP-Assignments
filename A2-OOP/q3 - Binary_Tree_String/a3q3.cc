#include "tstring.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;


void prettyPrint(TString::TNode * p, int indent=0) {
  if (indent) {
      std::cout << std::setw(indent) << ' ';
  }
  cout << "\"" << p->data << "\" size: " << p->size << endl;
  if (!p->left && !p->right) return;

  if(p->left) {
    prettyPrint(p->left,indent+1);
  } else {
    cout << setw(indent+1) << ' ';
    cout << "Null left child" << endl;
  }

  if(p->right) {
    prettyPrint(p->right,indent+1);
  } else {
    cout << setw(indent+1) << ' ';
    cout << "Null right child" << endl;
  }
}

void prettyPrint(TString *s){
    if (s && s->root)  prettyPrint(s->root);
}


void errMsg() {
    cerr << "Invalid test case." << endl;
}

bool badIndex(char c) {
    if (c < 'a' || c > 'd') {
        errMsg();
        return true;
    }
    return false;
}

// TEST HARNESS
// DO NOT MODIFY THIS FUNCTION IN ANY WAY
// Be sure to understand what the following does
// in order to create appropriate test cases.
int main() {
    const int arr_size = 4;
    TString **a = new TString*[arr_size];
    TString *tmp;
    for (int i = 0; i < arr_size; ++i) a[i] = nullptr;
    bool done = false;
    while (!done) {
        char c;
        char which;
        char lhs;
        char rhs;
        string s;
        stringstream ss;
        cin >> c; // reads r, +, d, p, s or q
        if (cin.eof()) break;
        switch(c) {
            case 'r': // Test string constructor.
                cin >> which; // reads a b c or d
                if (badIndex(which)) return 20;
                delete a[which-'a'];
                cin >> c; // Checks for opening quote.
                if (c!='"') {
                    errMsg();
                    return 20;
                }
                cin >> noskipws;
                while (cin >> c) {
                    if (c == '"') break; // Found closing quote.
                    ss << c;
                }
                cin >> skipws;
                a[which-'a'] = new TString(ss.str());
                ss.clear(); ss.str("");
                break;
            case 'c': // Test Copy Constructor.
                cin >> lhs; // Reads a b c or d.
                if (badIndex(lhs)) return 20;
                cin >> rhs; // Reads a b c or d
                if (badIndex(rhs)) return 20;
                if (a[rhs-'a'] == nullptr) {
                    errMsg();
                    return 20;
                }
                tmp = a[lhs-'a'];
                a[lhs-'a'] = new TString(*a[rhs-'a']);
                delete tmp;
                break;
            case '+': // Test concatenate
                cin >> which; // reads a b c or d
                if (badIndex(which)) return 20;
                cin >> lhs; // reads a b c or d
                if (badIndex(lhs)) return 20;
                if (a[lhs-'a'] == nullptr) {
                    errMsg();
                    return 20;
                }
                cin >> rhs; // reads a b c or d
                if (badIndex(rhs)) return 20;
                if (a[rhs-'a'] == nullptr) {
                    errMsg();
                    return 20;
                }
                // stores lhs + rhs in which.
                tmp = a[which-'a'];
                a[which-'a'] = new TString{*a[lhs-'a'] + *a[rhs-'a']};
                delete tmp;
                break;
            case 'i': // Tests index
                cin >> which; // reads a b c or d
                if (badIndex(which)) return 20;
                if (a[which-'a'] == nullptr) {
                    errMsg();
                    return 20;
                }
                long unsigned int ind;
                cin >> ind; // reads an index.
                char sep;
                cin >> sep; // reads one char to store in index.
                (*a[which-'a'])[ind] = sep;
                break;
            case '^': // tests insert.
                cin >> which;
                if (badIndex(which)) return 20;
                if (a[which-'a'] == nullptr) {
                    errMsg();
                    return 20;
                }
                cin >> ind;
                cin >> c; // Checks for opening quote.
                if (c!='"') {
                    errMsg();
                    return 20;
                }
                cin >> noskipws;
                while (cin >> c) {
                    if (c == '"') break; // Found closing quote.
                    ss << c;
                }
                cin >> skipws;
                a[which-'a']->insert(ss.str(),ind);
                ss.clear(); ss.str("");
                break;
            case 'p':
                cin >> which; // reads a b c or d
                if (badIndex(which)) return 20;
                if (a[which-'a'] == nullptr) {
                    errMsg();
                    return 20;
                }
                cout << (*a[which-'a']) << endl;
                break;
            case 'l': // Used to test your iterator functionality
                cin >> which;
                if (badIndex(which)) return 20;
                if (a[which-'a'] == nullptr) {
                    errMsg();
                    return 20;
                }
                cin >> lhs; // Reads in a character to be replaced
                cin >> rhs; // Reads in a characte  r to replace the above with
                for (auto &c : *a[which-'a']) {
                    if (c==lhs) c = rhs;
                }
                break;
            case 'd': //can be used to dump out the tree
                cin >> which; //reads a b c or d
                if (badIndex(which)) return 20;
                if (a[which-'a'] == nullptr) {
                    errMsg();
                    return 20;
                }
                prettyPrint(a[which-'a']);
                break;
            case 'q':
                done = true;
                break;
            default:
                errMsg();
                return 20;
        }
    }
    for (int i = 0; i < arr_size; ++i) delete a[i];
    delete[] a;
};
