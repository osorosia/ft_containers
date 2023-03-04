#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>

#include "../utils/pair.hpp"

// check
#define CHECK        true
#define CHECK_HEIGHT true
#define CHECK_AVL    false
#define CHECK_SIZE   true
// print
#define PRINT_HEIGHT false

#define DEBUG_NODE(node)                                                                           \
    {                                                                                              \
        std::cout << std::setw(16) << __func__ << ": " << std::setw(2) << node->value_.first;      \
        std::cout << " ";                                                                          \
        if (node->left_)                                                                           \
            std::cout << std::setw(2) << node->left_->value_.first;                                \
        else                                                                                       \
            std::cout << "__";                                                                     \
        std::cout << " ";                                                                          \
        if (node->right_)                                                                          \
            std::cout << std::setw(2) << node->right_->value_.first;                               \
        else                                                                                       \
            std::cout << "__";                                                                     \
        std::cout << std::endl;                                                                    \
    }

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
    node_type* find_min() { return left_ ? left_->find_min() : this; }
    node_type* find_max() { return right_ ? right_->find_max() : this; }
    bool       is_left() { return this == parent_->left_; }
    bool       is_right() { return this == parent_->right_; }
};

template < class T >
class tree_iterator {
public:
    typedef T                           value_type;
    typedef Node< value_type >          node_type;
    typedef tree_iterator< value_type > self_type;

    node_type* node_;

    tree_iterator(node_type* node)
        : node_(node) {}

    value_type& operator*() const { return node_->value_; }
};

template < class T >
class const_tree_iterator {
public:
    typedef T                                 value_type;
    typedef Node< value_type >                node_type;
    typedef const_tree_iterator< value_type > self_type;

    node_type* node_;

    const_tree_iterator(node_type* node)
        : node_(node) {}

    const value_type& operator*() const { return node_->value_; }
};

template < class Key,
           class T,
           class Compare   = std::less< Key >,
           class Allocator = std::allocator< std::pair< const Key, T > > >
class AVLTree {
public:
    typedef Key                                     key_type;
    typedef T                                       mapped_type;
    typedef std::pair< const Key, T >               value_type;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef Compare                                 key_compare;
    typedef Allocator                               allocator_type;
    typedef tree_iterator< value_type >             iterator;
    typedef const_tree_iterator< value_type >       const_iterator;
    typedef std::reverse_iterator< iterator >       reverse_iterator;
    typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

    typedef Node< value_type >                                      node_type;
    typedef typename Allocator::template rebind< node_type >::other node_allocator_type;

    node_type*          root_;
    node_type*          end_;
    size_type           size_;
    node_allocator_type node_alloc_;
    key_compare         comp_;

    AVLTree()
        : root_(NULL)
        , end_(NULL) // TODO:
        , size_(0)
        , node_alloc_(node_allocator_type())
        , comp_(key_compare()) {}

    explicit AVLTree(const Compare& comp, const Allocator& alloc = Allocator())
        : root_(NULL)
        , end_(NULL) // TODO:
        , size_(0)
        , node_alloc_(alloc)
        , comp_(comp) {
        end_ = allocate_end();
    }

    template < class InputIt >
    AVLTree(InputIt          first,
            InputIt          last,
            const Compare&   comp  = Compare(),
            const Allocator& alloc = Allocator())
        : root_(NULL)
        , end_(NULL) // TODO:
        , size_(0)
        , node_alloc_(alloc)
        , comp_(comp) {
        // TODO:
    }
    // map(const AVLTree& other);

    ~AVLTree() {
        deallocate_tree(root_);
        deallocate_node(end_);
    }

    std::pair< iterator, bool > insert(const value_type& value) {
        return insert_node(root_, value);
    }
    iterator insert(iterator pos, const value_type& value) {
        (void)pos;
        return (*insert(value)).first;
    }
    template < class InputIt >
    void insert(InputIt first, InputIt last) {
        for (InputIt it = first; it != last; it++) {
            insert(root_, *it);
        }
    }

    iterator  erase(iterator pos);
    iterator  erase(iterator first, iterator last);
    size_type erase(const Key& key) { return erase_node(root_, key); }

    // Iterators
    iterator begin() {
        if (size_ == 0)
            return end();
        node_type* node = find_min_node(root_);
        return iterator(node);
    }
    const_iterator begin() const {
        if (size_ == 0)
            return end();
        node_type* node = find_min_node(root_);
        return const_iterator(node);
    }

    iterator       end() { return iterator(end_); }
    const_iterator end() const { return const_iterator(end_); }

    reverse_iterator       rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator       rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    // Modifiers
    // clear
    // insert
    // erase
    // swap

    // Lookup
    size_type count(const Key& key) const { return find(key) != end(); }

    iterator find(const Key& key) {
        node_type* node = find_node(key);
        return node ? iterator(node) : end();
    }
    const_iterator find(const Key& key) const; // TODO:

    std::pair< iterator, iterator > equal_range(const Key& key) {
        return std::pair< iterator, iterator >(lower_bound(key), upper_bound(key));
    }
    // TODO:
    std::pair< const_iterator, const_iterator > equal_range(const Key& key) const;

    // lower_bound
    iterator lower_bound(const Key& key) {
        node_type* node = lower_bound_node(root_, key);
        return node ? iterator(node) : end();
    }
    // upper_bound
    iterator upper_bound(const Key& key) {
        node_type* node = upper_bound_node(root_, key);
        return node ? iterator(node) : end();
    }

    // Observers
    // key_comp
    // value_comp

    // private:
    node_type* allocate_node(const value_type& value) {
        node_type* node = node_alloc_.allocate(1);
        node_alloc_.construct(node, value);
        return node;
    }

    node_type* allocate_end() {
        node_type* node = node_alloc_.allocate(1);
        node_alloc_.construct(node, value_type());
        return node;
    }

    void deallocate_node(node_type* node) {
        if (node == NULL)
            return;
        node_alloc_.destroy(node);
        node_alloc_.deallocate(node, 1);
    }

    void deallocate_tree(node_type* node) {
        if (node == NULL)
            return;
        deallocate_tree(node->left_);
        deallocate_tree(node->right_);
        deallocate_node(node);
    }

    std::pair< iterator, bool > insert_node(node_type* node, const value_type& value) {
        if (root_ == NULL) {
            update_root(allocate_node(value));
            size_++;
            return std::pair< iterator, bool >(iterator(root_), true);
        }

        if (node->value_ == value) {
            return std::pair< iterator, bool >(iterator(node), false);
        } else if (value < node->value_) {
            if (node->left_) {
                return insert_node(node->left_, value);
            } else {
                node->left_          = allocate_node(value);
                node->left_->parent_ = node;
                update_height_to_root(node);
                size_++;
                rebalance(node);
                return std::pair< iterator, bool >(iterator(node->left_), true);
            }
        } else {
            if (node->right_) {
                return insert_node(node->right_, value);
            } else {
                node->right_          = allocate_node(value);
                node->right_->parent_ = node;
                update_height_to_root(node);
                size_++;
                rebalance(node);
                return std::pair< iterator, bool >(iterator(node->right_), true);
            }
        }
    }

    size_type erase_node(node_type* node, const Key& key) {
        if (node == NULL)
            return 0;

        if (get_key(node) > key) {
            return erase_node(node->left_, key);
        } else if (get_key(node) < key) {
            return erase_node(node->right_, key);
        } else {
            if (node->left_ == NULL && node->right_ == NULL) {
                // none
                replace_parent(node, NULL);
                update_height_to_root(node->parent_);
                size_--;
                rebalance(node->parent_);
            } else if (node->left_ == NULL) {
                // a right child
                replace_parent(node, node->right_);
                update_height_to_root(node->parent_);
                size_--;
                rebalance(node->parent_);
            } else if (node->right_ == NULL) {
                // a left child
                replace_parent(node, node->left_);
                update_height_to_root(node->parent_);
                size_--;
                rebalance(node->parent_);
            } else {
                // both children
                node_type* min        = node->right_->find_min();
                node_type* min_parent = min != node->right_ ? min->parent_ : min;
                replace_parent(min, min->right_);
                replace_node(node, min);
                update_height_to_root(min_parent);
                size_--;
                rebalance(min_parent);
            }
            deallocate_node(node);
            return 1;
        }
    }

    void rebalance(node_type* node) {
        if (node == NULL)
            return;
        // DEBUG_NODE(node);
        rotate(node);
        if (!is_root(node))
            rebalance(node->parent_);
    }

    long get_balance(node_type* node) {
        return (node->left_ ? node->left_->height_ : 0)
               - (node->right_ ? node->right_->height_ : 0);
    }

    void rotate(node_type* node) {
        int balance = get_balance(node);

        if (std::abs(balance) <= 1)
            return;
        DEBUG_NODE(node);

        if (balance > 1) {
            if (get_balance(node->left_) < 0)
                rotate_left(node->left_);
            rotate_right(node);
        } else {
            if (get_balance(node->right_) > 0)
                rotate_right(node->right_);
            rotate_left(node);
        }
    }

    void rotate_left(node_type* node) {
        DEBUG_NODE(node);

        node_type* x = node;
        node_type* y = node->right_;
        put_node_to_right(x, y->left_);
        replace_parent(x, y);
        put_node_to_left(y, x);

        update_height_to_root(x);
    }

    void rotate_right(node_type* node) {
        DEBUG_NODE(node);

        node_type* x = node->left_;
        node_type* y = node;
        put_node_to_left(y, x->right_);
        replace_parent(y, x);
        put_node_to_right(x, y);

        update_height_to_root(y);
    }

    void put_node_to_left(node_type* node, node_type* child) {
        node->left_ = child;
        if (child)
            child->parent_ = node;
    }

    void put_node_to_right(node_type* node, node_type* child) {
        node->right_ = child;
        if (child)
            child->parent_ = node;
    }

    node_type* lower_bound_node(node_type* node, const Key& key) {
        if (node == NULL)
            return NULL;

        if (get_key(node) == key) {
            return node;
        } else if (get_key(node) < key) {
            return has_right(node) ? lower_bound_node(node->right_, key) : NULL;
        } else {
            node_type* child = node->left_;
            if (child == NULL)
                return node;

            node_type* bottom = lower_bound_node(child, key);
            return bottom ? bottom : node;
        }
    }

    node_type* upper_bound_node(node_type* node, const Key& key) {
        if (node == NULL)
            return NULL;

        if (get_key(node) <= key) {
            return has_right(node) ? upper_bound_node(node->right_, key) : NULL;
        } else {
            node_type* child = node->left_;
            if (child == NULL)
                return node;

            node_type* bottom = upper_bound_node(child, key);
            return bottom ? bottom : node;
        }
    }

    void replace_node(node_type* node, node_type* next) {
        // parent
        next->parent_ = node->parent_;
        if (is_root(node)) {
            root_ = next;
        } else {
            if (is_left(node)) {
                next->parent_->left_ = next;
            } else {
                next->parent_->right_ = next;
            }
        }
        // left
        next->left_ = node->left_;
        if (next->left_) {
            next->left_->parent_ = next;
        }
        // right
        next->right_ = node->right_;
        if (next->right_) {
            next->right_->parent_ = next;
        }
        // height
        next->height_ = node->height_;
    }

    void replace_parent(node_type* node, node_type* next) {
        if (is_root(node)) {
            update_root(next);
            return;
        }

        if (is_left(node)) {
            node->parent_->left_ = next;
        } else {
            node->parent_->right_ = next;
        }
        if (next) {
            next->parent_ = node->parent_;
        }
    }

    int      get_height(node_type* node) { return node ? node->height_ : 0; }
    key_type get_key(node_type* node) { return node->value_.first; }
    bool     has_left(node_type* node) { return node->left_ != NULL; }
    bool     has_right(node_type* node) { return node->right_ != NULL; }
    bool     is_empty() { return root_ == NULL; }
    bool     is_left(node_type* node) { return node && node == node->parent_->left_; }
    bool     is_right(node_type* node) { return node && node == node->parent_->right_; }
    bool     is_root(node_type* node) { return node == root_; }
    void     update_left(node_type* node, node_type* child) {
        node->left_ = child;
        if (child)
            child->parent_ = node;
    }
    void update_right(node_type* node, node_type* child) {
        node->right_ = child;
        if (child)
            child->parent_ = node;
    }
    void update_root(node_type* node) {
        root_ = node;
        // TODO: end_で問題ない？
        if (node)
            node->parent_ = end_;
    }
    void update_height_to_root(node_type* node) {
        if (node == NULL)
            return;
        update_height(node);
        if (!is_root(node))
            update_height_to_root(node->parent_);
    }
    void update_height(node_type* node) {
        if (node == NULL)
            return;
        node->height_ = std::max(get_height(node->left_), get_height(node->right_)) + 1;
    }

    node_type* find_node(node_type* node, const Key& key) { return NULL; }

    // ----------------
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

        check_tree(root_);
        if (CHECK_HEIGHT)
            check_height(root_);
        if (CHECK_AVL)
            check_avl(root_);
        if (CHECK_SIZE)
            check_size();
        check_begin_end();
    }

    void check_size() { assert(size_ == calc_size(root_)); }

    size_type calc_size(node_type* node) {
        if (node == NULL)
            return 0;
        size_type left  = calc_size(node->left_);
        size_type right = calc_size(node->right_);
        return left + right + 1;
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

    void print(std::string title = "") {
        if (title != "")
            std::cout << "# " << title << std::endl;
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
        std::cout << prev_name << "-->" << name << "((" << node->value_.first;
        if (PRINT_HEIGHT)
            std::cout << ", " << node->height_;
        std::cout << "))" << std::endl;
    }
    void print_node_init(node_type* node, std::string name) {
        std::cout << name << "((";

        if (node) {
            std::cout << node->value_.first;
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
