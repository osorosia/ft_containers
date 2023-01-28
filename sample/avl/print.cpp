#include "avl.hpp"
#include <iostream>
using namespace std;

void print_node(Node* node, string name) {
    if (node->left) {
        cout << name << "-->" << name + "A"
             << "((" << node->left->val << "))" << endl;
        print_node(node->left, name + "A");
    }
    if (node->right) {
        cout << name << "-->" << name + "B"
             << "((" << node->right->val << "))" << endl;
        print_node(node->right, name + "B");
    }
}

void print(AVLTree& tree) {
    cout << "```mermaid" << endl;
    cout << "graph TB" << endl;

    cout << "O((" << tree.head->val << "))" << endl;
    print_node(tree.head, "O");

    cout << "```" << endl;
}
