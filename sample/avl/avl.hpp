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
    Node(long val) : left_(NULL), right_(NULL), parent_(NULL), val_(val) {}
};

struct AVLTree {
    Node* root_;

    AVLTree() : root_(NULL) {}

    void insert(long val) {
        if (root_ == NULL) {
            root_ = new Node(val);
        } else {
            insertNode(root_, val);
        }
    }

    void insertNode(Node* node, long val) {
        if (node->val_ > val) {
            if (node->left_) {
                insertNode(node->left_, val);
            } else {
                node->left_          = new Node(val);
                node->left_->parent_ = node;
            }
        } else if (node->val_ < val) {
            if (node->right_) {
                insertNode(node->right_, val);
            } else {
                node->right_          = new Node(val);
                node->right_->parent_ = node;
            }
        }
    }
};

#endif /* AVL_HPP */
