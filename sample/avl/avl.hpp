#ifndef AVL_HPP
#define AVL_HPP

#include <cassert>
#include <cstddef>
#include <iostream>
using namespace std;

struct Node {
    Node* left_;
    Node* right_;
    Node* parent_;
    long  height_;
    long  val_;

    Node(long val = 0, long height = 0)
        : left_(NULL)
        , right_(NULL)
        , parent_(NULL)
        , height_(height)
        , val_(val) {}

    Node* findMin() {
        if (left_ == NULL)
            return this;
        return left_->findMin();
    }
    Node* findMax() {
        if (right_ == NULL)
            return this;
        return right_->findMax();
    }

    bool isLeft() {
        if (parent_ == NULL)
            return false;
        return this == parent_->left_;
    }

    bool isRight() {
        if (parent_ == NULL)
            return false;
        return this == parent_->right_;
    }

    bool hasParent() {
        return parent_ != NULL;
    }

    void debug(string name) {
        cout << name << ": " << val_ << "  " << endl;

        cout << name << "->left: ";
        if (left_)
            cout << left_->val_;
        else
            cout << "NULL";
        cout << "  " << endl;

        cout << name << "->right: ";
        if (right_)
            cout << right_->val_;
        else
            cout << "NULL";
        cout << "  " << endl;

        cout << name << "->parent: ";
        if (parent_)
            cout << parent_->val_;
        else
            cout << "NULL";
        cout << "  " << endl;
        cout << "  " << endl;
    }
};

struct AVLTree {
    Node* root_;

    AVLTree()
        : root_(NULL) {}

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

    void erase(long val) { eraseNode(root_, val); }

    void eraseNode(Node* node, long val) {
        if (node == NULL) {
            return;
        }

        if (node->val_ > val) {
            eraseNode(node->left_, val);
        } else if (node->val_ < val) {
            eraseNode(node->right_, val);
        } else if (node->val_ == val) {
            if (node->left_ == NULL && node->right_ == NULL) {
                // none
                replaceNode(node, NULL);
                delete node;
            } else if (node->left_ == NULL) {
                // a right child
                assert(node->right_ != NULL);
                replaceNode(node, node->right_);
                delete node;
            } else if (node->right_ == NULL) {
                // a left child
                assert(node->left_ != NULL);
                replaceNode(node, node->left_);
                delete node;
            } else {
                // both children
                Node* tmp = node->right_->findMin();
                if (tmp->parent_->left_ == tmp) {
                    tmp->parent_->left_ = tmp->right_;
                } else {
                    tmp->parent_->right_ = tmp->right_;
                }

                tmp->left_   = node->left_;
                tmp->right_  = node->right_;
                tmp->parent_ = node->parent_;

                if (tmp->left_)
                    tmp->left_->parent_ = tmp;
                if (tmp->right_)
                    tmp->right_->parent_ = tmp;
                if (node->parent_) {
                    if (node->parent_->left_ == node) {
                        node->parent_->left_ = tmp;
                    } else {
                        node->parent_->right_ = tmp;
                    }
                } else {
                    root_ = tmp;
                }
                delete node;
            }
        }
    }

    void clear() { clearNode(root_); }
    void clearNode(Node* node) {
        if (node == NULL)
            return;
        if (node->left_)
            clearNode(node->left_);
        if (node->right_)
            clearNode(node->right_);
        delete node;
    }

    void replaceNode(Node* node, Node* next) {
        if (node->parent_ == NULL) {
            assert(node == root_);
            root_ = next;
            if (next)
                next->parent_ = NULL;
            return;
        }

        if (node->parent_->left_ == node) {
            node->parent_->left_ = next;
        } else {
            node->parent_->right_ = next;
        }
        if (next) {
            next->parent_ = node->parent_;
        }
    }

    void swapVal(Node *n0, Node *n1) {
        assert(n0 != NULL);
        assert(n1 != NULL);

        long tmp = n0->val_;
        n0->val_ = n1->val_;
        n1->val_ = tmp;
    }
};

#endif /* AVL_HPP */
