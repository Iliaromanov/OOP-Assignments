#ifndef TSTRING_H
#define TSTRING_H
#include <string>
#include <iostream>

struct TNode;

class TString {
    class TNode;
  public:
    TString(const std::string &);
    TString(const TString & );
    ~TString();
    // Concatenate two TStrings, the returned TString should not have any
    // connection to the TStrings used to create it, that is no future changes
    // to the operands should effect the returned TString and vice versa
    TString operator+( const TString & ) const;

    // Index operator. NOTE: returns a char& so the user can modify the char
    // in that index of the string. This should be taken into consideration
    // when deciding what data to use in your class.
    // Requires index < size of string represented by our TString.
    char &operator[] (const int index);

    // Insert the string denoted by the std::string into this TString at the
    // location immediately at index.
    // Requires index <= size of string represented by our TString.
    void insert(const std::string &s, const int index);

    // Iterator - You may not modify the contents of this structure at all!
    class TStringIter {
        TNode *p; // some private field to keep track of where the iterator is currently pointing to
        int ind;
        TStringIter(TNode *, int); // private constructor
      public:
        char &operator*(); // accesses the item the iterator is currently pointing to
        TStringIter &operator++(); // advances the iterator to the next item and returns the iterator
        bool operator!=(const TStringIter &); // returns true if both Iterators are different (do not point to the same item)
        friend class TString;
    };

    TStringIter begin(); // returns an Iterator pointing to the first element
    TStringIter end(); // returns an Iterator pointing past the last element (not to the last element itself, but after it)
  private:
      // Node class for representing nodes in the tree
    struct TNode {
        std::string data;
        TNode *left, *right;
        // Size of the string represented by this nodes left subtree, plus it's own
        // string data size.
        int size;
        TNode *parent;
        // You may add any additional TNode methods below here for your own use
        // You should NOT add any additional fields.
        TNode(std::string data, int size, TNode *left, TNode *right, TNode *parent);
        TNode(const TNode &other, TNode *parent = nullptr);
        ~TNode();
        // Inserts node at i
        void NodeInsert(const std::string &s, const int i);
        // Finds first parent that has the current node in its left sub-tree
        TNode *firstLeftParent();
        // increases all parents size values by amount
        void updateSizes(int left_size);
        // gets the right most child of the tree
        TNode *RmAndReturnRightmostChild();
        char &operator[] (const int index);
        // returns the leftmost node
        TNode *leftmostNode();
        // returns the rightmost node
        TNode *rightmostNode();

        // End TNode, changes from the above comment must stop here.
    };
    TNode *root;
    int length;
    friend void prettyPrint(TString *);
    friend void prettyPrint(TString::TNode *, int);
    friend TStringIter;
    // Print the string represented by our TString.
    friend std::ostream& operator<<(std::ostream &, const TString &);
    // You may add any fields/methods below here for your own use.
    // Print TNode
    friend std::ostream& operator<<(std::ostream &, const TString::TNode &);
};
#endif
