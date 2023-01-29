#include "avl.hpp"
#include <iostream>
using namespace std;

void print_node(Node* node, string name) {
    assert(!node->left_ || node == node->left_->parent_);
    assert(!node->right_ || node == node->right_->parent_);

    if (node->left_) {
        cout << name << "-->" << name + "A"
             << "((" << node->left_->val_ << "))" << endl;
        print_node(node->left_, name + "A");
    }
    if (node->right_) {
        cout << name << "-->" << name + "B"
             << "((" << node->right_->val_ << "))" << endl;
        print_node(node->right_, name + "B");
    }
}

void print(AVLTree& tree) {
    cout << "```mermaid" << endl;
    cout << "graph TB" << endl;

    if (tree.root_) {
        cout << "O((" << tree.root_->val_ << "))" << endl;
        print_node(tree.root_, "O");
    }

    cout << "```" << endl;
}
