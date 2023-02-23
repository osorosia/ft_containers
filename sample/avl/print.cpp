#include "avl.hpp"
#include <iostream>
using namespace std;

void print_node(AVLTree& tree, Node* node, string name) {
    // node check
    assert(node->left_ == NULL || node == node->left_->parent_);
    assert(node->right_ == NULL || node == node->right_->parent_);
    if (node != tree.root_) {
        assert(node->parent_);
        assert(node->parent_->left_ == node || node->parent_->right_ == node);
    } else {
        assert(node->parent_ == NULL);
    }

    // left
    if (!node->left_ && node->right_)
        cout << name << "-->" << name + "A"
             << "((.))" << endl;
    if (node->left_) {
        cout << name << "-->" << name + "A"
             << "((" << node->left_->val_ << "))" << endl;
        print_node(tree, node->left_, name + "A");
    }

    // right
    if (node->left_ && !node->right_)
        cout << name << "-->" << name + "B"
             << "((.))" << endl;
    if (node->right_) {
        cout << name << "-->" << name + "B"
             << "((" << node->right_->val_ << "))" << endl;
        print_node(tree, node->right_, name + "B");
    }
}

void print(AVLTree& tree) {
    cout << "```mermaid" << endl;
    cout << "graph TB" << endl;

    if (tree.root_) {
        cout << "O((" << tree.root_->val_ << "))" << endl;
        print_node(tree, tree.root_, "O");
    }

    cout << "```" << endl;
}
