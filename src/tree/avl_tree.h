#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>

#include "../utils/pair.hpp"

namespace ft {

template < class T >
struct Node {
    typedef T                  value_type;
    typedef Node< value_type > node_type;
    typedef node_type*         node_pointer;

    node_pointer left_;
    node_pointer right_;
    node_pointer parent_;
    value_type   value_;
    int          height_;

    Node()
        : left_(NULL)
        , right_(NULL)
        , parent_(NULL)
        , height_(1);
    , value_(value_type()) {}

    Node(value_type value)
        : left_(NULL)
        , right_(NULL)
        , parent_(NULL)
        , height_(1);
    , value_(value) {}

    node_pointer next() {
        if (right_)
            return right_->find_min();
        node_pointer node = this;
        if (node->parent_)
            return node;
    }
    node_pointer prev() {
        if (left_)
            return left_->find_max();
    }
    node_pointer find_min() {
        if (left_)
            return left_->find_min();
        return this;
    }
    node_pointer find_max() {
        if (right_)
            return right_->find_max();
        return this;
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
};

template < class T >
class tree_iterator {
public:
    typedef T                           value_type;
    typedef Node< value_type >          node_type;
    typedef node_type*                  node_pointer;
    typedef tree_iterator< value_type > tree_iterator_type;

    node_pointer node;
};

template < class Key,
           class T,
           class Compare   = std::less< Key >,
           class Allocator = std::allocator< std::pair< const Key, T > > >
class AVLTree {
public:
    typedef Key                               key_type;
    typedef T                                 mapped_type;
    typedef std::pair< const Key, T >         value_type;
    typedef std::size_t                       size_type;
    typedef std::ptrdiff_t                    difference_type;
    typedef Compare                           key_compare;
    typedef Allocator                         allocator_type;
    typedef tree_iterator< value_type >       iterator;
    typedef std::reverse_iterator< iterator > reverse_iterator;
    typedef Allocator                         allocator_type;

    typedef Node< value_type >                                      node_type;
    typedef node_type*                                              node_pointer;
    typedef typename Allocator::template rebind< node_type >::other node_allocator_type;

    node_pointer        root_;
    node_pointer        end_;
    node_allocator_type node_alloc_;

    AVLTree()
        : root_(NULL)
        , end_(NULL)
        , node_alloc_(node_allocator_type()) {}

    iterator begin() {
        node_pointer node = find_min_node();
        if (node)
            return iterator();
    }

    std::pair< iterator, bool > insert(const value_type& value) {}

    iterator insert(iterator pos, const value_type& value) {}

    template < class InputIt >
    void insert(InputIt first, InputIt last);

    iterator find(const Key& key) { Node* node = find_node(key); }

    node_pointer find_node(node_pointer node, const Key& key) { if () }

    // ----------------
    node_pointer find_min_node(node_pointer node) {
        if (node->left_)
            return find_min_node(node->left_);
        return node;
    }

    node_pointer find_max_node(node_pointer node) {
        if (node->right_)
            return find_max_node(node->right_);
        return node;
    }

    void check() {}

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

} // namespace ft

#endif /* AVL_TREE_H */
