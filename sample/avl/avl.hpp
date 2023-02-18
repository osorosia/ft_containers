#ifndef AVL_HPP
#define AVL_HPP

#include <cassert>
#include <cstddef>

struct Node {
    Node* parent_;
    Node* left_;
    Node* right_;
    long  val_;

    Node(long val) : parent_(NULL), left_(NULL), right_(NULL), val_(val) {}

    void insertNode(long num) {
        if (val_ == num)
            return;
        else if (num < val_) {
            if (left_ == NULL) {
                left_          = new Node(num);
                left_->parent_ = this;
            } else {
                left_->insertNode(num);
            }
        } else {
            if (right_ == NULL) {
                right_          = new Node(num);
                right_->parent_ = this;
            } else {
                right_->insertNode(num);
            }
        }
    }

    Node* eraseNode(long num) {
        if (num == val_) {
            if (!left_)
                return right_;
            else if (!right_)
                return left_;
            else {
                Node* tmpRight = right_;
                Node* tmpLeft  = left_;

                Node* node     = right_;
                Node* prevNode = this;
                while (node->left_) {
                    prevNode = node;
                    node     = node->left_;
                }
                prevNode->left_ = NULL;
                return node;
            }
        } else {
            if (num < val_)
                left_ = left_->eraseNode(num);
            else
                right_ = left_->eraseNode(num);
            return this;
        }
    }
};

struct AVLTree {
    Node* root_;

    AVLTree() : root_(NULL) {}

    void insert(long num) {
        if (!root_) {
            root_ = new Node(num);
            return;
        }

        root_->insertNode(num);
    }
    void erase(long num) {
        if (!root_)
            return;
        root_ = root_->eraseNode(num);
    }
};

#endif /* AVL_HPP */
