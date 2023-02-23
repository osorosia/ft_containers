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
    long  val_;

    Node()
        : left_(NULL)
        , right_(NULL)
        , parent_(NULL)
        , val_(0) {}
    Node(long val)
        : left_(NULL)
        , right_(NULL)
        , parent_(NULL)
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
                if (node->parent_) {
                    if (node->parent_->left_ == node) {
                        node->parent_->left_ = NULL;
                    } else {
                        node->parent_->right_ = NULL;
                    }
                } else {
                    root_ = NULL;
                }
                delete node;
            } else if (node->left_ == NULL) {
                // a right child
                assert(node->right_ != NULL);
                if (node->parent_) {
                    if (node->parent_->left_ == node) {
                        node->parent_->left_ = node->right_;
                    } else {
                        node->parent_->right_ = node->right_;
                    }
                    node->right_->parent_ = node->parent_;
                } else {
                    root_ = node->right_;
                }
                delete node;
            } else if (node->right_ == NULL) {
                // a left child
                assert(node->left_ != NULL);
                if (node->parent_) {
                    if (node->parent_->left_ == node) {
                        node->parent_->left_ = node->left_;
                    } else {
                        node->parent_->right_ = node->left_;
                    }
                    node->left_->parent_ = node->parent_;
                } else {
                    root_ = node->left_;
                    node->left_->parent_ = NULL;
                }
                delete node;
            } else {
                // both children
                Node* tmp = node->right_->findMin();
                if (tmp->parent_->left_ == tmp) {
                    tmp->parent_->left_ = NULL;
                } else {
                    tmp->parent_->right_ = NULL;
                }

                tmp->left_   = node->left_;
                tmp->right_  = node->right_;
                tmp->parent_ = node->parent_;

                tmp->left_->parent_  = tmp;
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
    
    void clear() {
        clearNode(root_);
    }
    void clearNode(Node *node) {
        if (node == NULL)
            return;
        if (node->left_)
            clearNode(node->left_);
        if (node->right_)
            clearNode(node->right_);
        delete node;
    }
};

#endif /* AVL_HPP */
