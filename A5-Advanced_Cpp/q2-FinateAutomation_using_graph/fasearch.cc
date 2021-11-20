#include <iostream>
#include <memory>

#include "finiteautomaton.h"

using namespace std;

int main() {
    auto fa = make_unique<FiniteAutomaton>();
    std::vector<FiniteAutomaton::Node *> nodes;
    char cmd;

    while (true) {
        cin >> cmd;

        // Quit if requested
        if (cin.fail() || cmd == 'q') break;

        // Perform the command
        switch (cmd) {
            case 'n':
            {
                nodes.emplace_back(fa->addNode());
                cout << "Node " << nodes.size() << " created." << endl;
                break;
            }

            case 'e':
            {
                int from, to;
                char c;
                cin >> from >> to >> c;
                fa->addEdge(nodes[from-1], nodes[to-1], c);
                cout << "Edge added." << endl;
                break;
            }

            case 's':
            {
                int from, len;
                cin >> from >> len;
                cout << "Results:" << endl;
                for (auto res : fa->search(nodes[from-1], len))
                    cout << res << endl;
                break;
            }

            case 'c':
            {
                nodes.clear();
                fa = make_unique<FiniteAutomaton>();
                cout << "Done." << endl;
                break;
            }

            default:
                cout << "Unrecognized command!" << endl;
        }
    }

    return 0;
}
