#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string a = "012345";
    istringstream ss{a};
    string b;
    ss >> b;
    cout << ss.eof() << ss.fail() << endl;
}