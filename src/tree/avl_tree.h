#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>

#include "../utils/pair.hpp"

#define CHECK        true
#define CHECK_HEIGHT true
#define CHECK_AVL    true
#define PRINT_HEIGHT true

namespace ft {

template < class T >
struct Node {
    typedef T                  value_type;
    typedef Node< value_type > node_type;

    node_type* left_;
    node_type* right_;
    node_type* parent_;
    value_type value_;
    int        height_;

    Node()
        : left_(NULL)
        , right_(NULL)
        , parent_(NULL)
        , height_(1)
        , value_(value_type()) {}

    Node(value_type value)
        : left_(NULL)
        , right_(NULL)
        , parent_(NULL)
        , height_(1)
        , value_(value) {}

    node_type* next() {
        if (right_)
            return right_->find_min();
        node_type* node = this;
        if (node->parent_)
            return node;
    }
    node_type* prev() {
        if (left_)
            return left_->find_max();
    }
    node_type* find_min() {
        if (left_)
            return left_->find_min();
        return this;
    }
    node_type* find_max() {
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
    typedef tree_iterator< value_type > tree_iterator_type;

    node_type* node_;

    tree_iterator(node_type* node)
        : node_(node) {}
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

    typedef Node< value_type >                                      node_type;
    typedef typename Allocator::template rebind< node_type >::other node_allocator_type;

    node_type*          root_;
    node_type*          end_;
    node_allocator_type node_alloc_;

    AVLTree()
        : root_(NULL)
        , end_(NULL)
        , node_alloc_(node_allocator_type()) {}

    iterator begin() {
        node_type* node = find_min_node();
        if (node)
            return iterator();
    }

    node_type* allocate_node(const value_type& value) {
        node_type* node = node_alloc_.allocate(1);
        node_alloc_.construct(node, value);
        return node;
    }

    std::pair< iterator, bool > insert(const value_type& value) {
        return insert_node(root_, value);
    }
    iterator insert(iterator pos, const value_type& value) {
        // TODO: implement
        (void)pos;
        return (*insert(value)).first;
    }
    template < class InputIt >
    void insert(InputIt first, InputIt last) {
        for (InputIt it = first; it != last; it++) {
            insert(root_, *it);
        }
    }

    std::pair< iterator, bool > insert_node(node_type* node, const value_type& value) {
        if (root_ == NULL) {
            root_ = allocate_node(value);
            return std::pair< iterator, bool >(iterator(root_), true);
        }

        if (node->value_ == value) {
            return std::pair< iterator, bool >(iterator(node), false);
        } else if (node->value_ < value) {
            if (node->left_) {
                return insert_node(node->left_, value);
            } else {
                node->left_          = allocate_node(value);
                node->left_->parent_ = node;
                return std::pair< iterator, bool >(iterator(node->left_), true);
            }
        } else {
            if (node->right_) {
                return insert_node(node->right_, value);
            } else {
                node->right_          = allocate_node(value);
                node->right_->parent_ = node;
                return std::pair< iterator, bool >(iterator(node->right_), true);
            }
        }
    }

    iterator find(const Key& key) { node_type* node = find_node(key); }

    node_type* find_node(node_type* node, const Key& key) { return NULL; }

    // ----------------
    bool is_root(node_type* node) { return node == root_; }

    node_type* find_min_node(node_type* node) {
        if (node->left_)
            return find_min_node(node->left_);
        return node;
    }

    node_type* find_max_node(node_type* node) {
        if (node->right_)
            return find_max_node(node->right_);
        return node;
    }

    void check() {
        if (!CHECK)
            return;

        if (CHECK_HEIGHT)
            check_height(root_);
        if (CHECK_AVL)
            check_avl(root_);
        check_tree(root_);
        check_begin_end();
    }

    void check_begin_end() {
        // TODO:
    }

    void check_tree(node_type* node) {
        if (node == NULL)
            return;

        if (node->left_) {
            assert(node == node->left_->parent_);
            assert(node->value_ > node->left_->value_);
        }
        if (node->right_) {
            assert(node == node->right_->parent_);
            assert(node->value_ < node->right_->value_);
        }

        check_tree(node->left_);
        check_tree(node->right_);
    }

    void check_height(node_type* node) {
        if (node == NULL)
            return;

        if (node->left_ == NULL && node->right_ == NULL) {
            assert(node->height_ == 1);
        } else if (node->left_ == NULL) {
            assert(node->height_ == node->right_->height_ + 1);
        } else if (node->right_ == NULL) {
            assert(node->height_ == node->left_->height_ + 1);
        } else {
            int left  = node->left_->height_;
            int right = node->right_->height_;
            assert(node->height_ == std::max(left, right) + 1);
        }

        check_height(node->left_);
        check_height(node->right_);
    }

    void check_avl(node_type* node) {
        if (node == NULL)
            return;

        int left  = node->left_ ? node->left_->height_ : 0;
        int right = node->right_ ? node->right_->height_ : 0;
        assert(std::abs(left - right) <= 1);

        check_avl(node->left_);
        check_avl(node->right_);
    }

    void print() {
        std::cout << "```mermaid" << std::endl;
        std::cout << "graph TB" << std::endl;

        std::string name = "O";
        print_node_init(root_, name);
        print_tree(root_, name);

        std::cout << "```" << std::endl;
    }
    void print_tree(node_type* node, std::string name) {
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
    void print_node(node_type* node, std::string prev_name, std::string name) {
        if (node == NULL)
            return;
        std::cout << prev_name << "-->" << name << "((" << node->val_;
        if (PRINT_HEIGHT)
            std::cout << ", " << node->height_;
        std::cout << "))" << std::endl;
    }
    void print_node_init(node_type* node, std::string name) {
        std::cout << name << "((";

        if (node) {
            std::cout << node->val_;
            if (PRINT_HEIGHT)
                std::cout << ", " << node->height_;
        } else {
            std::cout << ".";
        }

        std::cout << "))" << std::endl;
    }
    void print_node_null(std::string prev_name, std::string name) {
        std::cout << prev_name << "-->" << name << "((.))" << std::endl;
    }
};

} // namespace ft

#endif /* AVL_TREE_H */
