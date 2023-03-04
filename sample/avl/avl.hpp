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

    Node* find_min() {
        if (left_ == NULL)
            return this;
        return left_->find_min();
    }
    Node* find_max() {
        if (right_ == NULL)
            return this;
        return right_->find_max();
    }

    bool is_left() {
        if (parent_ == NULL)
            return false;
        return this == parent_->left_;
    }

    bool is_right() {
        if (parent_ == NULL)
            return false;
        return this == parent_->right_;
    }

    bool has_parent() { return parent_ != NULL; }

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
            insert_node(root_, val);
        }
    }

    void insert_node(Node* node, long val) {
        if (node->val_ > val) {
            if (node->left_) {
                insert_node(node->left_, val);
            } else {
                node->left_          = new Node(val, 1);
                node->left_->parent_ = node;
                update_height_to_root(node);
                rebalance(node);
            }
        } else if (node->val_ < val) {
            if (node->right_) {
                insert_node(node->right_, val);
            } else {
                node->right_          = new Node(val, 1);
                node->right_->parent_ = node;
                update_height_to_root(node);
                rebalance(node);
            }
        }
    }

    void erase(long val) { erase_node(root_, val); }

    void erase_node(Node* node, long val) {
        if (node == NULL) {
            return;
        }

        if (node->val_ > val) {
            erase_node(node->left_, val);
        } else if (node->val_ < val) {
            erase_node(node->right_, val);
        } else if (node->val_ == val) {
            if (node->left_ == NULL && node->right_ == NULL) {
                // none
                replace_parent(node, NULL);

                update_height_to_root(node->parent_);
                rebalance(node->parent_);
                delete node;
            } else if (node->left_ == NULL) {
                // a right child
                replace_parent(node, node->right_);

                update_height_to_root(node->parent_);
                rebalance(node->parent_);
                delete node;
            } else if (node->right_ == NULL) {
                // a left child
                replace_parent(node, node->left_);

                update_height_to_root(node->parent_);
                rebalance(node->parent_);
                delete node;
            } else {
                // both children
                Node* tmp = node->right_->find_min();
                replace_parent(tmp, tmp->right_);
                swap_val(node, tmp);

                update_height_to_root(tmp->parent_);
                rebalance(tmp->parent_);
                delete tmp;
            }
        }
    }

    void clear() { clear_node(root_); }
    void clear_node(Node* node) {
        if (node == NULL)
            return;
        if (node->left_)
            clear_node(node->left_);
        if (node->right_)
            clear_node(node->right_);
        delete node;
    }

    void replace_parent(Node* node, Node* next) {
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

    void swap_val(Node* n0, Node* n1) {
        assert(n0 != NULL);
        assert(n1 != NULL);

        long tmp = n0->val_;
        n0->val_ = n1->val_;
        n1->val_ = tmp;
    }

    void update_height_to_root(Node* node) {
        if (node == NULL)
            return;
        update_height(node);
        update_height_to_root(node->parent_);
    }

    void update_height(Node* node) {
        node->height_ = max(getHeight(node->left_), getHeight(node->right_)) + 1;
    }

    long getHeight(Node* node) { return node ? node->height_ : 0; }

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
                rotate_left(node->left_);
            }
            rotate_right(node);
        } else {
            if (get_balance(node->right_) > 0) {
                rotate_right(node->right_);
            }
            rotate_left(node);
        }
    }
    void rotate_left(Node* node) {
        assert(get_balance(node) < 0);
        Node* x = node;
        Node* y = node->right_;
        put_node_to_right(x, y->left_);
        replace_parent(x, y);
        put_node_to_left(y, x);

        update_height_to_root(x);
    }
    void rotate_right(Node* node) {
        assert(get_balance(node) > 0);
        Node* x = node->left_;
        Node* y = node;
        put_node_to_left(y, x->right_);
        replace_parent(y, x);
        put_node_to_right(x, y);

        update_height_to_root(y);
    }

    void put_node_to_left(Node* node, Node* child) {
        assert(node);
        node->left_ = child;
        if (child)
            child->parent_ = node;
    }

    void put_node_to_right(Node* node, Node* child) {
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
