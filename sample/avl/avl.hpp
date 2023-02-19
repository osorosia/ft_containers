#ifndef AVL_HPP
#define AVL_HPP

#include <cassert>
#include <cstddef>

struct Node {
    Node* left_;
    Node* right_;
    Node* parent_;
    long  val_;

    Node() : left_(NULL), right_(NULL), parent_(NULL), val_(0) {}
    Node(long value) : left_(NULL), right_(NULL), parent_(NULL), val_(value) {}
};

struct AVLTree {
    Node* root_;

    AVLTree() : root_(NULL) {}

    void insert(long value) {
        if (root_ == NULL) {
            root_ = new Node(value);
        } else {
            insertNode(root_, value);
        }
    }

    void insertNode(Node* node, long value) {
        if (node->val_ > value) {
            if (node->left_) {
                insertNode(node->left_, value);
            } else {
                node->left_          = new Node(value);
                node->left_->parent_ = node;
            }
        } else if (node->val_ < value) {
            if (node->right_) {
                insertNode(node->right_, value);
            } else {
                node->right_          = new Node(value);
                node->right_->parent_ = node;
            }
        }
    }
};

#endif /* AVL_HPP */
