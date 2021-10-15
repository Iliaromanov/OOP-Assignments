// Array operations from CMD
#include <iostream>
using namespace std;

struct IntArray {
  int size; //number of elements the array currently holds
  int capacity; //number of elements the array could hold,
                //given current memory allocation to contents
  int *contents; //the integer array
};

IntArray readIntArray();

void addToIntArray(IntArray& ia);

void printIntArray(const IntArray& ia);


// Do not change this function!

int main() {  // Test harness for IntArray functions.
  bool done = false;
  IntArray a[4];
  a[0].contents = a[1].contents = a[2].contents = a[3].contents = nullptr;

  while(!done) {
    char c;
    char which;

    // Note:  prompt prints to stderr, so it should not occur in .out files
    cerr << "Command?" << endl;  // Valid commands:  ra, rb, rc, rd,
                                 //                  +a, +b, +c, +d,
                                 //                  pa, pb, pc, pd, 
                                 //                  q
    cin >> c;  // Reads r, +, p, or q
    if (cin.eof()) break;
    switch(c) {
      case 'r':
        cin >> which;  // Reads a, b, c, or d
        delete [] a[which-'a'].contents;
        a[which-'a'].contents = nullptr;
        a[which-'a'] = readIntArray();
        break;
      case '+':
        cin >> which;  // Reads a, b, c, or d
        addToIntArray(a[which-'a']);
        break;
      case 'p':
        cin >> which;  // Reads a, b, c, or d
        printIntArray(a[which-'a']);
        cout << "Capacity: " << a[which-'a'].capacity << endl;
        break;
      case 'q':
        done = true;
    }
  }

  for (int i = 0; i < 4; ++i) delete [] a[i].contents;
}


IntArray readIntArray() {
  IntArray new_ia{0, 0, nullptr};

  int val;
  while (true) {
    cin >> val;
    if (cin.fail()) {
      cin.clear();
      cin.ignore();
      break;
    }
    if (!new_ia.capacity) {
      new_ia.capacity = 5;
      int *contents = new int[new_ia.capacity]; // allocate capacity of 5 for first time
      new_ia.contents = contents;
    } else if (new_ia.capacity == new_ia.size) {
      new_ia.capacity *= 2;
      int *contents = new int[new_ia.capacity]; // double the cap
      for (int i = 0; i < new_ia.size; ++i) {
        contents[i] = new_ia.contents[i]; // copy the current contents
      }
      delete [] new_ia.contents;
      new_ia.contents = contents;
    }
    new_ia.contents[new_ia.size] = val;
    ++new_ia.size;
  }

  return new_ia;
}


void addToIntArray(IntArray& ia) {
  int val;
  while (true) {
    cin >> val;
    if (cin.fail()) {
      cin.clear();
      cin.ignore();
      break;
    }
    if (!ia.capacity) {
      ia.capacity = 5;
      int *contents = new int[ia.capacity]; // allocate capacity of 5 for first time
      ia.contents = contents;
    } else if (ia.capacity == ia.size) {
      ia.capacity *= 2;
      int *contents = new int[ia.capacity]; // double the cap
      for (int i = 0; i < ia.size; ++i) {
        contents[i] = ia.contents[i]; // copy the current contents
      }
      delete [] ia.contents;
      ia.contents = contents;
    }
    ia.contents[ia.size] = val;
    ++ia.size;
  }
}

void printIntArray(const IntArray& ia) {
  for (int i = 0; i < ia.size; ++i) {
    cout << ia.contents[i] << " ";
  }
  cout << endl;
}