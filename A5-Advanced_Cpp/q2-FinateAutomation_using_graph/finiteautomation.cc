#include "finiteautomaton.h"
#include <algorithm>
#include <string>
using namespace std;


FiniteAutomaton::Node *FiniteAutomaton::addNode() {
    nodes.push_back(make_unique<Node>(nodes.size()));
    return nodes.back().get();
}

// Add an edge (link) to the graph
void FiniteAutomaton::addEdge(Node *a, Node *b, char c) {
    a->addEdge(b->getIndex(), c);
}

// Search for strings of a given length
vector<string> FiniteAutomaton::search(Node *start, int len) {
    vector<string> result = {};
    if (!len) return result; // if len is zero, return empty vector

    for (auto &edge : start->edges) {
        vector<string> v;
        string s{edge.second}; // convert the edge label from char to str
        v.push_back(s); // make it the first char of any generated strings from this node

        // build the subset of the result vec that starts from following this edge
        vector<string> sub_result = buildSubset(
            nodes.at(edge.first).get(), len - 1, v
        );

        // empty string indicates that it was impossible to build a string of length len
        //  by following this edge, so we don't merge this sub_result to result
        if (sub_result.back() == "") continue; 

        // Otherwise add the strings in sub_result to the final result
        for (auto s : sub_result) result.push_back(s);
    }

    // Sort and return the result
    sort(result.begin(), result.end());
    return result;
}

// Recursively build a subset of strings of length len starting at given node
vector<string> FiniteAutomaton::buildSubset(Node *start, int len, vector<string> cur_strs) {
    if (!len) return cur_strs; // if len=0, the end of the strings has been reached
    vector<string> result = {""};

    for (auto &edge : start->edges) {
        // add current edge label to strings in subset
        vector<string> v;
        for (auto s : cur_strs) v.push_back(s + edge.second);
        // build the subset of the result vec that starts from following this edge
        vector<string> sub_result = buildSubset(
            nodes.at(edge.first).get(), len - 1, v
        );

        // empty string indicates that it was impossible to build a string of length len
        //  by following this edge, so we don't merge this sub_result to result
        if (sub_result.back() == "") {
            continue;
        } else { // otherwise, remove the "" and add the strings in subset to result
            if(result.size() == 1 && result.back() == "") result.pop_back();
            for (auto s : sub_result) result.push_back(s);
        }
    }
    return result;
}

FiniteAutomaton::Node::Node(int index) : index{index} {}

void FiniteAutomaton::Node::addEdge(int to, char c) { edges[to] = c; }

int FiniteAutomaton::Node::getIndex() { return index; }