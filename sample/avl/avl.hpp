#ifndef AVL_HPP
#define AVL_HPP

#include "config.hpp"
#include <cassert>
#include <cmath>
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

    bool hasParent() { return parent_ != NULL; }

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
            root_ = new Node(val, 1);
        } else {
            insertNode(root_, val);
        }
    }

    void insertNode(Node* node, long val) {
        if (node->val_ > val) {
            if (node->left_) {
                insertNode(node->left_, val);
            } else {
                node->left_          = new Node(val, 1);
                node->left_->parent_ = node;
                calcHeightToRoot(node);
                rebalance(node);
            }
        } else if (node->val_ < val) {
            if (node->right_) {
                insertNode(node->right_, val);
            } else {
                node->right_          = new Node(val, 1);
                node->right_->parent_ = node;
                calcHeightToRoot(node);
                rebalance(node);
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
                calcHeightToRoot(node->parent_);
                rebalance(node->parent_);
                delete node;
            } else if (node->left_ == NULL) {
                // a right child
                assert(node->right_ != NULL);

                replaceNode(node, node->right_);
                calcHeightToRoot(node->parent_);
                rebalance(node->parent_);
                delete node;
            } else if (node->right_ == NULL) {
                // a left child
                assert(node->left_ != NULL);

                replaceNode(node, node->left_);
                calcHeightToRoot(node->parent_);
                rebalance(node->parent_);
                delete node;
            } else {
                // both children
                Node* tmp = node->right_->findMin();
                replaceNode(tmp, tmp->right_);
                calcHeightToRoot(tmp->parent_);
                rebalance(tmp->parent_);

                swapVal(node, tmp);
                delete tmp;
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

    void swapVal(Node* n0, Node* n1) {
        assert(n0 != NULL);
        assert(n1 != NULL);

        long tmp = n0->val_;
        n0->val_ = n1->val_;
        n1->val_ = tmp;
    }

    void calcHeightToRoot(Node* node) {
        if (node == NULL)
            return;
        calcHeight(node);
        calcHeightToRoot(node->parent_);
    }

    void calcHeight(Node* node) {
        node->height_ = max(node->left_ ? node->left_->height_ : 0L,
                            node->right_ ? node->right_->height_ : 0L)
                        + 1;
    }

    void rebalance(Node* node) {
        if (node == NULL)
            return;

        rotate(node);
        rebalance(node->parent_);
    }

    long get_balance(Node* node) {
        return (node->left_ ? node->left_->height_ : 0)
               - (node->right_ ? node->right_->height_ : 0);
    }

    void rotate(Node* node) {
        assert(node != NULL);
        long balance = get_balance(node);

        if (-1 <= balance && balance <= 1)
            return;

        if (balance > 1) {
            if (get_balance(node->left_) < 0) {
                rotateLeft(node->left_);
            }
            rotateRight(node);
        } else {
            if (get_balance(node->right_) > 0) {
                rotateRight(node->right_);
            }
            rotateLeft(node);
        }
    }
    void rotateLeft(Node* node) {
        assert(get_balance(node) < 0);
        Node* x = node;
        Node* y = node->right_;
        putNodeToRight(x, y->left_);
        replaceNode(x, y);
        putNodeToLeft(y, x);
    
        calcHeightToRoot(x);
    }
    void rotateRight(Node* node) {
        assert(get_balance(node) > 0);
        Node* x = node->left_;
        Node* y = node;
        putNodeToLeft(y, x->right_);
        replaceNode(y, x);
        putNodeToRight(x, y);
    
        calcHeightToRoot(y);
    }

    void putNodeToLeft(Node* node, Node* child) {
        assert(node);
        node->left_ = child;
        if (child)
            child->parent_ = node;
    }

    void putNodeToRight(Node* node, Node* child) {
        assert(node);
        node->right_ = child;
        if (child)
            child->parent_ = node;
    }

    void print() {
        cout << "```mermaid" << endl;
        cout << "graph TB" << endl;

        string name = "O";
        print_node_init(root_, name);
        print_tree(root_, name);

        cout << "```" << endl;
    }
    void print_tree(Node* node, string name) {
        if (node == NULL)
            return;

        // check node
        assert(node->left_ == NULL || node == node->left_->parent_);
        assert(node->right_ == NULL || node == node->right_->parent_);
        if (node != root_) {
            assert(node->parent_);
            assert(node->parent_->left_ == node || node->parent_->right_ == node);
        } else {
            assert(node->parent_ == NULL);
        }

        // check height
        if (CHECK_HEIGHT) {
            if (node->left_ == NULL && node->right_ == NULL) {
                assert(node->height_ == 1);
            } else if (node->left_ == NULL) {
                assert(node->height_ == node->right_->height_ + 1);
            } else if (node->right_ == NULL) {
                assert(node->height_ == node->left_->height_ + 1);
            } else {
                long childMaxHeight = max(node->left_->height_, node->right_->height_);
                assert(node->height_ == childMaxHeight + 1);
            }
        }

        // left
        if (!node->left_ && node->right_)
            print_node_null(name, name + "A");
        print_node(node->left_, name, name + "A");
        print_tree(node->left_, name + "A");

        // right
        if (node->left_ && !node->right_)
            print_node_null(name, name + "B");
        print_node(node->right_, name, name + "B");
        print_tree(node->right_, name + "B");
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
    void print_node_null(string prev_name, string name) {
        cout << prev_name << "-->" << name << "((.))" << endl;
    }
};

#endif /* AVL_HPP */
