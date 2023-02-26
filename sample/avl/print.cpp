#include "avl.hpp"
#include "config.hpp"
#include <iostream>
using namespace std;

void print_node_null(string prev_name, string name) {
    cout << prev_name << "-->" << name << "((.))" << endl;
}

void print_node(Node* node, string prev_name, string name) {
    if (node == NULL)
        return;
    cout << prev_name << "-->" << name << "((" << node->val_;
    if (PRINT_HEIGHT)
        cout << ", " << node->height_;
    cout << "))" << endl;
}

void print_node_init(Node* node, string name) {
    cout << name << "((";

    if (node) {
        cout << node->val_;
        if (PRINT_HEIGHT)
            cout << ", " << node->height_;
    } else {
        cout << ".";
    }

    cout << "))" << endl;
}

void print_tree(AVLTree& tree, Node* node, string name) {
    if (node == NULL)
        return;

    // check node
    assert(node->left_ == NULL || node == node->left_->parent_);
    assert(node->right_ == NULL || node == node->right_->parent_);
    if (node != tree.root_) {
        assert(node->parent_);
        assert(node->parent_->left_ == node || node->parent_->right_ == node);
    } else {
        assert(node->parent_ == NULL);
    }

    // check height
    if (CHECK_HEIGHT) {
        if (node->parent_) {
            assert(node->height_ == node->parent_->height_ - 1);
        }
        if (node->left_) {
            assert(node->height_ == node->left_->height_ + 1);
        }
        if (node->right_) {
            assert(node->height_ == node->right_->height_ + 1);
        }
        if (node->left_ == NULL && node->right_ == NULL) {
            assert(node->height_ == 1);
        }
    }

    // left
    if (!node->left_ && node->right_)
        print_node_null(name, name + "A");
    print_node(node->left_, name, name + "A");
    print_tree(tree, node->left_, name + "A");

    // right
    if (node->left_ && !node->right_)
        print_node_null(name, name + "B");
    print_node(node->right_, name, name + "B");
    print_tree(tree, node->right_, name + "B");
}

void print(AVLTree& tree) {
    cout << "```mermaid" << endl;
    cout << "graph TB" << endl;

    string name = "O";
    print_node_init(tree.root_, name);
    print_tree(tree, tree.root_, name);

    cout << "```" << endl;
}
