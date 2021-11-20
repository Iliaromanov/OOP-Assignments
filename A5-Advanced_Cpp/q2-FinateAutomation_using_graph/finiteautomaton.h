#ifndef FINITEAUTOMATON_H
#define FINITEAUTOMATON_H

#include <memory>
#include <string>
#include <vector>
#include <map>

class FiniteAutomaton {
    public:
    /* Note: Define node however you wish. Its public and private APIs are
     * entirely yours to define. */
    class Node;

    /* Note: You may not extend the *public* API of FiniteAutomaton. However,
     * adding a default constructor is not extending the public API, since an
     * automatic default constructor exists without defining one. So, if you
     * need a constructor, you may define a default constructor. */

    // Add a new node to this finite automaton
    Node *addNode();

    // Add an edge (link) to the graph
    void addEdge(Node *a, Node *b, char c);

    // Search for strings of a given length
    std::vector<std::string> search(Node *start, int len);

    class Node {
        int index;
        std::map<int, char> edges;
        public:
            Node(int index);
            int getIndex();
            void addEdge(int to, char c);
            // edges will be a map with the (key, value) pairs
            //  given by (to_index, edge_label)
            

        friend class FiniteAutomaton;
    };

    private:
        std::vector<std::unique_ptr<Node>> nodes;
        // method to build vectors of strings by recursively traversing the graph
        std::vector<std::string> buildSubset(Node *start, int len, std::vector<std::string> cur_strings);
};

#endif
